#ifndef Maps_H
#define Maps_H

#include "Header.h"
#include "tinyxml2.h"

struct Object
{
	std::string name;//�������� ���������� name ���� string
	sf::Rect<float> rect;//��� Rect � �������� ����������
};

struct Layer//����
{
	std::vector<sf::Sprite> tiles;//���������� � ������ �����
};

class Maps//������� ����� - �������
{
public:
	bool LoadFromFile(std::string filename);//���������� false ���� �� ���������� ���������
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);//������ ������ � ��� �������
	std::vector<Object> GetAllObjects();//������ ��� ������� � ��� �������
	void Draw(sf::RenderWindow &window);//������ � ����

private:
	int width, height, tileWidth, tileHeight;//� tmx ����� width height � ������,����� ������ �����
	int firstTileID;//�������� ���� ������� �����
	sf::Rect<float> drawingBounds;//������ ����� ����� ������� ������
	sf::Texture tilesetImage;//�������� �����
	std::vector<Object> objects;//������ ���� �������, ������� �� �������
	std::vector<Layer> layers;
};

///////////////////////////////////////

bool Maps::LoadFromFile(std::string filename)//���������-��������� � ������� ������ ��� ������ 
{
	layers.clear();
	objects.clear();

	tinyxml2::XMLDocument MapsFile(filename.c_str());//��������� ���� � TiXmlDocument
	MapsFile.LoadFile(filename.c_str());

	tinyxml2::XMLElement *map;
	map = MapsFile.FirstChildElement("map");

	width = atoi(map->Attribute("width"));//��������� �� ����� ����� �� ��������
	height = atoi(map->Attribute("height"));//�� ��������, ������� �������� ��� ������ � 
	tileWidth = atoi(map->Attribute("tilewidth"));//������� ���������
	tileHeight = atoi(map->Attribute("tileheight"));

	// ����� �������� �������� � ������������� ������� �����
	tinyxml2::XMLElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - ���� �� �������� � ���������� image
	tinyxml2::XMLElement *image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");

	// �������� ��������� �������
	sf::Image img;
	img.loadFromFile(imagepath);
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//�����������

	// �������� ���������� �������� � ����� ��������
	int columns = tilesetImage.getSize().x / (tileWidth);
	int rows = tilesetImage.getSize().y / (tileHeight);

	// ������ �� ��������������� ����������� (TextureRect)
	std::vector<sf::Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
	for (int x = 0; x < columns; x++)
	{
		sf::Rect<int> rect;

		rect.top = (y) * (tileHeight);
		rect.height = tileHeight;
		rect.left = (x) * (tileWidth);
		rect.width = tileWidth;

		subRects.push_back(rect);
	}

	// ������ �� ������
	tinyxml2::XMLElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		tinyxml2::XMLElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		tinyxml2::XMLElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		int x = 0;
		int y = 0;

		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;

			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * (tileWidth), y * (tileHeight));
				layer.tiles.push_back(sprite);//���������� � ���� ������� ������
			}

			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	// ������ � ���������
	tinyxml2::XMLElement *objectGroupElement;
	// ���� ���� ���� ��������
	objectGroupElement = map->FirstChildElement("objectgroup");
	while (objectGroupElement)
	{
		// ���������� <object>
		tinyxml2::XMLElement *objectElement;
		objectElement = objectGroupElement->FirstChildElement("object");

		while (objectElement)
		{
			// �������� ��� ������ - ���, ���, �������, � ��
			std::string objectType;
			if (objectElement->Attribute("type") != NULL)
			{
				objectType = objectElement->Attribute("type");
			}
			std::string objectName;
			if (objectElement->Attribute("name") != NULL)
			{
				objectName = objectElement->Attribute("name");
			}
			int x = atoi(objectElement->Attribute("x"));
			int y = atoi(objectElement->Attribute("y"));

			int width, height;

			sf::Sprite sprite;
			sprite.setTexture(tilesetImage);
			sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
			sprite.setPosition(x, y);

			if (objectElement->Attribute("width") != NULL)
			{
				width = atoi(objectElement->Attribute("width"));
				height = atoi(objectElement->Attribute("height"));
			}
			else
			{
				width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
				height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
				sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
			}

			// ��������� �������
			Object object;
			object.name = objectName;

			sf::Rect <float> objectRect;
			objectRect.top = y;
			objectRect.left = x;
			objectRect.height = height;
			objectRect.width = width;
			object.rect = objectRect;
			objects.push_back(object);
			objectElement = objectElement->NextSiblingElement("object");
		}
		objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
	}
}

Object Maps::GetObject(std::string name)
{
	// ������ ������ ������ � �������� ������
	for (int i = 0; i < objects.size(); i++)
	if (objects[i].name == name)
		return objects[i];
}

std::vector<Object> Maps::GetObjects(std::string name)
{
	// ��� ������� � �������� ������
	std::vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
	if (objects[i].name == name)
		vec.push_back(objects[i]);

	return vec;
}


std::vector<Object> Maps::GetAllObjects()
{
	return objects;
};

void Maps::Draw(sf::RenderWindow &window)
{
	// ������ ��� ����� (������� �� ������!)
	for (int layer = 0; layer < layers.size(); layer++)
	for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		window.draw(layers[layer].tiles[tile]);
}

#endif