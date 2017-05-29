#include "Header.h" //���������� header

bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	int MapsID = 0;

	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::Fullscreen); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	//window.setFramerateLimit(60); //����� ������ � �������

	bool pressedBut = false; //���������� ��� �������� ������� ������ ����(

	//-----------------------------------��� ����������� ������������-----------------------
	
	Player p1(500, 500); //������� ������ ������ �����
	Player p2(600, 600); //������� ������ ������ �����
	UdpSocket socket;
	socket.setBlocking(false);
	string stringip;
	IpAddress myip = IpAddress::getLocalAddress();
	IpAddress enemyip(stringip);
	Maps map;
	vector <Object> obj;
	MainMenu menu;
	ChooseHost choosinghost;
	WaitingForPlayers waitplayers;
	WaitingForServer waitserver;
	Help helpwindow;
	ChooseMap choosemap;
	ConnectToIp connect;
	float p1posX, p1posY;
	float p2posX, p2posY, p2Rotation, mousePos2pX, mousePos2pY;
	MainGame maingame(p1,p2,MapsID,hostChoosed);
	//Color color(255, 0, 0);
	obj = map.GetObjects("solid");
	
	int enemyHealth, myHealth;
	Vector2f MousePos;
	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{	
		MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		if (gamestate == 0) { return false; } //����� �� ����
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); } //������� ����
		else if (gamestate == 2) { choosinghost.render(window, gamestate, hostChoosed, socket, pressedBut, myip, enemyip, MapsID, map, obj); } //����� �����
		else if (gamestate == 3) { waitplayers.render(window, gamestate, pressedBut, socket, myip, enemyip,MapsID); } // �������� �������
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut, myip, enemyip,MapsID,map); } // �������� �����
		else if (gamestate == 6) { helpwindow.render(window, gamestate, pressedBut); } // ���� ������
		else if (gamestate == 7) { choosemap.render(window, gamestate, pressedBut, MapsID, map, obj); } //����� ����� ��� �����
		else if (gamestate == 8) { connect.render(window, gamestate, pressedBut, enemyip,stringip); }
		else if (gamestate == 5) { maingame.render(window, p1, p2, pressedBut, hostChoosed, gamestate, socket, enemyip, map,obj,MousePos); }
		else if (gamestate == 9) { return true; } // ������� ����
		if (!Mouse::isButtonPressed(Mouse::Button::Left)) // �������� �� ��������� ������� �������
			pressedBut = false;
	}
}

void gameRunning() 
{
	if (startGame()) { gameRunning(); }
}

int main() //������� ������� ����
{

	gameRunning();
	return 0;
}


