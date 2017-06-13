#ifndef Maps_H
#define Maps_H

#include "Header.h"
#include "tinyxml2.h"

struct Object
{
	std::string name;//объявили переменную name типа string
	sf::Rect<float> rect;//тип Rect с нецелыми значениями
};

struct Layer//слои
{
	std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
};

class Maps//главный класс - уровень
{
public:
	bool LoadFromFile(std::string filename);//возвращает false если не получилось загрузить
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);//выдаем объект в наш уровень
	std::vector<Object> GetAllObjects();//выдаем все объекты в наш уровень
	void Draw(sf::RenderWindow &window);//рисуем в окно

private:
	int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
	int firstTileID;//получаем айди первого тайла
	sf::Rect<float> drawingBounds;//размер части карты которую рисуем
	sf::Texture tilesetImage;//текстура карты
	std::vector<Object> objects;//массив типа Объекты, который мы создали
	std::vector<Layer> layers;
};

///////////////////////////////////////

bool Maps::LoadFromFile(std::string filename)//двоеточия-обращение к методам класса вне класса 
{
	layers.clear();
	objects.clear();

	tinyxml2::XMLDocument MapsFile(filename.c_str());//загружаем файл в TiXmlDocument
	MapsFile.LoadFile(filename.c_str());

	tinyxml2::XMLElement *map;
	map = MapsFile.FirstChildElement("map");

	width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
	height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
	tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
	tileHeight = atoi(map->Attribute("tileheight"));

	// Берем описание тайлсета и идентификатор первого тайла
	tinyxml2::XMLElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - путь до картинки в контейнере image
	tinyxml2::XMLElement *image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");

	// пытаемся загрузить тайлсет
	sf::Image img;
	img.loadFromFile(imagepath);
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//сглаживание

	// получаем количество столбцов и строк тайлсета
	int columns = tilesetImage.getSize().x / (tileWidth);
	int rows = tilesetImage.getSize().y / (tileHeight);

	// вектор из прямоугольников изображений (TextureRect)
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

	// работа со слоями
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
				layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
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

	// работа с объектами
	tinyxml2::XMLElement *objectGroupElement;
	// если есть слои объектов
	objectGroupElement = map->FirstChildElement("objectgroup");
	while (objectGroupElement)
	{
		//  контейнер <object>
		tinyxml2::XMLElement *objectElement;
		objectElement = objectGroupElement->FirstChildElement("object");

		while (objectElement)
		{
			// получаем все данные - тип, имя, позиция, и тд
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

			// экземпляр объекта
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
	// только первый объект с заданным именем
	for (int i = 0; i < objects.size(); i++)
	if (objects[i].name == name)
		return objects[i];
}

std::vector<Object> Maps::GetObjects(std::string name)
{
	// все объекты с заданным именем
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
	// рисуем все тайлы (объекты не рисуем!)
	for (int layer = 0; layer < layers.size(); layer++)
	for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		window.draw(layers[layer].tiles[tile]);
}

#endif