#include <SFML/Graphics.hpp>

class Game {
public:

    Game();

    void run();

private:
    void update(sf::Time deltaTime);

    void processEvents();

    void render();

    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false, mIsMovingRight = false;
    float PlayerSpeed;
    sf::Time TimePerFrame;

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
};

Game::Game()
        : mWindow(sf::VideoMode(640, 480), "SFML Application"), mPlayer() {
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(sf::Color::Cyan);
    PlayerSpeed = 250.f;
    TimePerFrame = sf::seconds(1.f / 200.f);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
        }
    }

}

void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;
    mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

int main() {
    Game game;
    game.run();
    return 0;
}
