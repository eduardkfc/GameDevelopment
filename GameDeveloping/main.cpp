#include "Header.h" //���������� header

bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	int levelID;

	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	window.setFramerateLimit(60); //����� ������ � �������

	bool pressedBut = false; //���������� ��� �������� ������� ������ ����(
	bool gameLife = true;
	//-----------------------------------��� ����������� ������������-----------------------
	
	Player p1(500, 500); //������� ������ ������ �����
	Player p2(600, 600); //������� ������ ������ �����
	UdpSocket socket;
	socket.setBlocking(false);
	IpAddress myip = IpAddress::getLocalAddress();
	IpAddress enemyip("192.168.43.232");
	

	MainMenu menu;
	ChooseHost choosinghost;
	WaitingForPlayers waitplayers;
	WaitingForServer waitserver;
	Help helpwindow;
	ChooseMap choosemap;
	MainGame maingame(levelID);
	//Color color(255, 0, 0);
	
	
	float p2posX, p2posY, p2Rotation, mousePos2pX,mousePos2pY;
	int enemyHealth, myHealth;

	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{	
		if (gamestate == 0) { return false; }
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); }
		else if (gamestate == 2) { choosinghost.render(window, gamestate, hostChoosed, socket, pressedBut, myip, enemyip); }
		else if (gamestate == 3) { waitplayers.render(window, gamestate, pressedBut, socket, myip, enemyip); }
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut, myip, enemyip); }
		else if (gamestate == 6) { helpwindow.render(window, gamestate, pressedBut); }
		else if (gamestate == 7) { choosemap.render(window, gamestate, pressedBut,levelID); }
		else if (gamestate == 5) { maingame.render(window, p1, p2, pressedBut, hostChoosed, gamestate, socket, enemyip); }
		if (!Mouse::isButtonPressed(Mouse::Button::Left)) // �������� �� ��������� ������� �������
			pressedBut = false;
		if (gameLife == false) { return false; }
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


