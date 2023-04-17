// basado en el libro SFML Game Development :)

#include "Game.h"
#include <cmath>


Game::Game()
	: mWindow(sf::VideoMode(800, 600), "Pizza Panic")
	, mTexture()
	, mPlayer()
    , mItem()
	, pView(sf::FloatRect(0.f, 0.f, mWindow.getSize().x, mWindow.getSize().y))
	, mainMenu(m_font, m_menuBackground)
{
	// Initialize MainMenu
	if (!m_font.loadFromFile("Fonts/ka1.ttf"))
	{
		// Handle loading error
		cout << ("Error al cargar el font del menú.");
	}
    if (!m_font2.loadFromFile("Fonts/font2.ttf"))
    {
        // Handle loading error
        cout << ("Error al cargar el font del item.");
    }
	if (!m_menuBackground.loadFromFile("Images/FondoMenuPrueba.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el fondo del menu.");
	}
	MainMenu mainMenu(m_font, m_menuBackground);

	// Player
	if (!mTexture.loadFromFile("Images/robot-idle.gif"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo.");
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(2500.f, 2500.f);
	mPlayer.setScale(0.18f, 0.18f);
    mPlayerCollider = mPlayer.getGlobalBounds();

    // Item
//    if (!mItemTexture.loadFromFile("Images/Eagle.png"))
//    {
//        // Handle loading error
//        cout << ("Error al cargar el archivo del Item.");
//    }
//    mItem.setTexture(mItemTexture);
//    mItem.setPosition(2500.f, 2490.f);
//    mItem.setScale(1.f, 1.f);

    // ITEM COLLIDER

    // sf::FloatRect mItemCollider(2500,2480,20,20);
    // mItemCollider = mItem.getGlobalBounds();

    prompt.setFont(m_font2);
    prompt.setString("¡Presiona espacio para recoger el item!");
    prompt.setPosition(2500.f,2470.f);
    // prompt.setPosition(mItem.getPosition().x, mItem.getPosition().y - 20);

	// Hitboxes
	this->HitBoxPlayer();
	this->HitBoxChiwis();
	this->HitBoxSheguis();
	this->HitBoxSoruya();
	this->HitBoxMindy();
    this->HitBoxItem();

	// Tilemap
	if (!background.load("Images/Tileset.png", sf::Vector2u(48, 48)))
	{
		// Handle loading error
		cout << ("Error al cargar el mapa.");
	}

	// Collision objects
	if (!objects.load("Images/Tileset.png", sf::Vector2u(48, 48)))
	{
		// Handle loading error
		cout << ("Error al cargar los objetos del mapa.");
	}

	// Music
	if (!music.openFromFile("Audios/CreepyForest.wav")) // canci�n de prueba nom�s
	{
		// Handle loading error
		cout << ("Error al cargar el audio.");
	}
	music.play();
	music.setVolume(20.f);

}

void Game::showMainMenu()
{

	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			mainMenu.handleEvent(event);
			if (event.type == sf::Event::Closed)
			{
				mWindow.close();
			}
		}

		mWindow.clear();
		mWindow.draw(mainMenu);
		mWindow.display();

		if (mainMenu.getSelectedOption() == MainMenu::Option::Jugar || mainMenu.getSelectedOption() == MainMenu::Option::Salir)
			break;
	}
}

void Game::run()
{
	showMainMenu();

	// If Play button is clicked, start the game
	if (mainMenu.getSelectedOption() == MainMenu::Option::Jugar) {

		// Keep track of the player's initial position
		sf::Vector2f previousPlayerPos = mPlayer.getPosition();

		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		while (mWindow.isOpen())
		{
			processEvents();
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				processEvents();
				update(TimePerFrame);
			}
			render();
		}
	}

}

void Game::processEvents()
// User input
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mainMenu.handleEvent(event);
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

void Game::update(sf::Time deltaTime)
// Update what happens in game
{
	sf::Vector2f movement(0.f, 0.f);
    sf::Vector2f mItemColliderPosition(2500, 2480);
    sf::Vector2f mItemColliderSize(20, 20);
    sf::FloatRect mItemCollider(mItemColliderPosition, mItemColliderSize);

	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;


	// Camera follows player
	pView.setCenter(mPlayer.getPosition());
	pView.setSize(1000.f, 1000.f);
	mWindow.setView(pView);

    // Check item collision
    if(mPlayerCollider.intersects(mItemCollider)){

        // Display prompt to press pickup key
        dinaisAntunez = true;

        if(sf::Keyboard::isKeyPressed(teclaItem)) {

            // Perform item pickup logic here
            cout << "Item picked up!" << std::endl;
            mItem.setPosition(-1000.f,-1000.f);
        }
    }

	//**************SHEGUIS**************************************************
	
	float dxsheguis = mPlayer.getPosition().x - hitboxsheguis.getPosition().x;
	float dysheguis = mPlayer.getPosition().y - hitboxsheguis.getPosition().y;
	float distancesheguis = sqrt(pow(dxsheguis, 2.f) + pow(dysheguis, 2.f));

	float dxsheguisaux = 2000 - hitboxsheguis.getPosition().x;
	float dysheguisaux = 2100 - hitboxsheguis.getPosition().y;
	float distancesheguisaux = sqrt(pow(dxsheguisaux, 2.f) + pow(dysheguisaux, 2.f));

	sf::Vector2f unitVectorsheguis(dxsheguis / distancesheguis, dysheguis / distancesheguis);
	sf::Vector2f unitVectorsheguisaux(dxsheguisaux / (distancesheguisaux + 0.001), dysheguisaux / (distancesheguisaux + 0.001));

	sf::Vector2f velocitysheguis = unitVectorsheguis * (SheguisSpeed);
	sf::Vector2f velocitysheguisaux = unitVectorsheguisaux * (SheguisSpeed);

	if (distancesheguis <= RadioDetected && distancesheguisaux <= RadioDetected) {
		hitboxsheguis.move(velocitysheguis * deltaTime.asSeconds());
	}
	else {
		hitboxsheguis.move(velocitysheguisaux * deltaTime.asSeconds());
	}
	//************************************************************************


	//**************SORUYA****************************************************
	
	float dxsoruya = mPlayer.getPosition().x - hitboxsoruya.getPosition().x;
	float dysoruya = mPlayer.getPosition().y - hitboxsoruya.getPosition().y;
	float distancesoruya = sqrt(pow(dxsoruya, 2.f) + pow(dysoruya, 2.f));

	float dxsoruyaaux = 3000 - hitboxsoruya.getPosition().x;
	float dysoruyaaux = 700 - hitboxsoruya.getPosition().y;
	float distancesoruyaaux = sqrt(pow(dxsoruyaaux, 2.f) + pow(dysoruyaaux, 2.f));

	sf::Vector2f unitVectorsoruya(dxsoruya / distancesoruya, dysoruya / distancesoruya);
	sf::Vector2f unitVectorsoruyaaux(dxsoruyaaux / (distancesoruyaaux + 0.001), dysoruyaaux / (distancesoruyaaux + 0.001));

	sf::Vector2f velocitysoruya = unitVectorsoruya * (SoruyaSpeed);
	sf::Vector2f velocitysoruyaaux = unitVectorsoruyaaux * (SoruyaSpeed);

	if (distancesoruya <= RadioDetected && distancesoruyaaux <= RadioDetected) {
		hitboxsoruya.move(velocitysoruya * deltaTime.asSeconds());
	}
	else {
		hitboxsoruya.move(velocitysoruyaaux * deltaTime.asSeconds());
	}
	//**************************************************************************


	//**************MINDY****************************************************

	float dxmindy = mPlayer.getPosition().x - hitboxmindy.getPosition().x;
	float dymindy = mPlayer.getPosition().y - hitboxmindy.getPosition().y;
	float distancemindy = sqrt(pow(dxmindy, 2.f) + pow(dymindy, 2.f));

	float dxmindyaux = 1816 - hitboxmindy.getPosition().x;
	float dymindyaux = 1416 - hitboxmindy.getPosition().y;
	float distancemindyaux = sqrt(pow(dxmindyaux, 2.f) + pow(dymindyaux, 2.f));

	sf::Vector2f unitVectormindy(dxmindy / distancemindy, dymindy / distancemindy);
	sf::Vector2f unitVectormindyaux(dxmindyaux / (distancemindyaux + 0.001), dymindyaux / (distancemindyaux + 0.001));

	sf::Vector2f velocitymindy = unitVectormindy * (MindySpeed);
	sf::Vector2f velocitymindyaux = unitVectormindyaux * (MindySpeed);

	if (distancemindy <= RadioDetected && distancemindyaux <= RadioDetected) {
		hitboxmindy.move(velocitymindy * deltaTime.asSeconds());
	}
	else {
		hitboxmindy.move(velocitymindyaux * deltaTime.asSeconds());
	}
	//**************************************************************************


	//*************CHIWIS*******************************************************
	float dxchiwis = mPlayer.getPosition().x - hitboxchiwis.getPosition().x;
	float dychiwis = mPlayer.getPosition().y - hitboxchiwis.getPosition().y;
	float distancechiwis = sqrt(pow(dxchiwis, 2.f) + pow(dychiwis, 2.f));
	sf::Vector2f unitVectorchiwis(dxchiwis / distancechiwis, dychiwis / distancechiwis);
	sf::Vector2f velocitychiwis = unitVectorchiwis * (ChiwisSpeed);
	hitboxchiwis.move(velocitychiwis * deltaTime.asSeconds());
	//**************************************************************************
	


	// Keep track of the player's previous position
	sf::Vector2f previousPlayerPos = mPlayer.getPosition();


	mPlayer.move(movement * deltaTime.asSeconds());
	hitboxplayer.move(movement * deltaTime.asSeconds());
	
	
	
	



	// Create Collidable object for the player
	Collidable playerCollidable(1, mPlayer.getGlobalBounds(), true);


	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(playerCollidable.m_bounds)) {

			// Handle collision
			mPlayer.setPosition(previousPlayerPos);
			hitboxplayer.setPosition(previousPlayerPos);
			//cout << "Collision with object!\n";

		}
	}

    cout << "x: " << mPlayer.getPosition().x << ", y: " << mPlayer.getPosition().y << std::endl;
}



void Game::HitBoxPlayer()
{
	this->hitboxplayer.setPosition(720.f, 725.f);
	this->hitboxplayer.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxplayer.setFillColor(sf::Color::Transparent);
	this->hitboxplayer.setOutlineColor(sf::Color::Transparent);
	this->hitboxplayer.setOutlineThickness(4.f);
    this->mPlayerCollider.
}

void Game::HitBoxChiwis()
{
	this->hitboxchiwis.setPosition(3250.f, 1215.f);
	this->hitboxchiwis.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxchiwis.setFillColor(sf::Color::Transparent);
	this->hitboxchiwis.setOutlineColor(sf::Color::Cyan);
	this->hitboxchiwis.setOutlineThickness(6.f);
}

void Game::HitBoxSheguis()
{
	this->hitboxsheguis.setPosition(2000.f, 2100.f);
	this->hitboxsheguis.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxsheguis.setFillColor(sf::Color::Transparent);
	this->hitboxsheguis.setOutlineColor(sf::Color::Red);
	this->hitboxsheguis.setOutlineThickness(6.f);
}

void Game::HitBoxSoruya()
{
	this->hitboxsoruya.setPosition(3000.f, 700.f);
	this->hitboxsoruya.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxsoruya.setFillColor(sf::Color::Transparent);
	this->hitboxsoruya.setOutlineColor(sf::Color::Black);
	this->hitboxsoruya.setOutlineThickness(6.f);
}

void Game::HitBoxMindy()
{
	this->hitboxmindy.setPosition(1816.f, 1466.f);
	this->hitboxmindy.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxmindy.setFillColor(sf::Color::Transparent);
	this->hitboxmindy.setOutlineColor(sf::Color::Black);
	this->hitboxmindy.setOutlineThickness(6.f);
}

void Game::HitBoxItem()
{
    this->hitboxItem.setPosition(2500.f,2490.f);
    this->hitboxItem.setSize(sf::Vector2f(40.f, 40.f));
    this->hitboxItem.setFillColor(sf::Color::Transparent);
    this->hitboxItem.setOutlineColor(sf::Color::Green);
    this->hitboxItem.setOutlineThickness(6.f);
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(background);
	mWindow.draw(objects);
	mWindow.draw(mPlayer);
    mWindow.draw(mItem);
	mWindow.draw(hitboxplayer);
	mWindow.draw(hitboxchiwis);
	mWindow.draw(hitboxsheguis);
	mWindow.draw(hitboxsoruya);
	mWindow.draw(hitboxmindy);
    mWindow.draw(hitboxItem);
    if (dinaisAntunez) mWindow.draw(prompt);
	mWindow.display();
}

/* void Game::Seguir(float xP, float yP, float xM, float yM, float Pox, float Poy, float Speed, sf::RectangleShape hitboxmascota, sf::Time deltaTime) {
	float dx = xP - xM;
	float dy = yP - yM;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));

	float dxaux = Pox - xM;
	float dyaux = Poy - yM;
	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));

	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));

	sf::Vector2f velocity = unitVector * (Speed);
	sf::Vector2f velocityaux = unitVectoraux * (Speed);

	if (distance <= RadioDetected && distanceaux <= RadioDetected) {
		hitboxmascota.move(velocity * deltaTime.asSeconds());
	}
	else {
		hitboxmascota.move(velocityaux * deltaTime.asSeconds());
	}
}
*/
