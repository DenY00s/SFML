#include <SFML/Graphics.hpp>
#include <iostream>
sf::Image image;
sf::Texture texture;
sf::Sprite sprite;

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::None);
    window.setFramerateLimit(60);
    sf::CircleShape shape;
    shape.setRadius(100);
    shape.setPosition(100, 400);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(100, 100);
    sf::RectangleShape rectangle(sf::Vector2f(1500, 5));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setPosition(0, 400);
    sf::RectangleShape rectangle2(sf::Vector2f(1500, 500));
    rectangle2.setFillColor(sf::Color::Black);
    rectangle2.setPosition(0, 405);
    sf::Clock clk;
    int circle_speed = 150;

    bool drag = false;
    sf::Vector2i click_offs;
    double dy = 0;
    bool onGround = true;
    image.loadFromFile("C:\Users\PC\OneDrive\Документы\DENIS\SFML_project1\SFML_project1\x64\image.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setPosition(50, 50);

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::U)
                {
                    shape.setFillColor(sf::Color::Magenta);
                    std::cout << "Color:Magenta" << std::endl;
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Key::U)
                {
                    shape.setFillColor(sf::Color::Yellow);
                    std::cout << "Color:hz" << std::endl;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition() - window.getPosition();
                    sf::Vector2f shape_pos = shape.getPosition();
                    auto dist = (mouse_pos.x - shape_pos.x) * (mouse_pos.x - shape_pos.x) + (mouse_pos.y - shape_pos.y) * (mouse_pos.y - shape_pos.y);
                    if (dist < 10000)
                    {
                        drag = true;
                        click_offs = sf::Vector2i(shape_pos.x - mouse_pos.x, shape_pos.y - mouse_pos.y);
                        std::cout << click_offs.x << "" << click_offs.y << std::endl;
                    }

                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (drag)
                {
                    drag = false;

                }
            }
        }

        float elapsed = clk.restart().asMilliseconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            onGround = false;
            dy = -5;
        }
        if (!onGround)
            dy += elapsed * 0.005;
        shape.move(0, dy);
        if (shape.getPosition().y > 300)
        {
            onGround = true;
            dy = 0;
        }
        sf::Vector2i mouse_pos = sf::Mouse::getPosition() - window.getPosition();
        sf::Vector2f shape_pos = shape.getPosition();
        auto dist = (mouse_pos.x - shape_pos.x) * (mouse_pos.x - shape_pos.x) + (mouse_pos.y - shape_pos.y) * (mouse_pos.y - shape_pos.y);
        if (dist < 10000)
        {
            shape.setFillColor(sf::Color::Green);
        }
        else
        {
            shape.setFillColor(sf::Color::Yellow);

        }
        if (drag)

            shape.setPosition(mouse_pos.x + click_offs.x, mouse_pos.y + click_offs.y);



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            shape.move(circle_speed * elapsed / 1000, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            shape.move(-circle_speed * elapsed / 1000, 0);

        window.clear(sf::Color::Cyan);
        window.draw(shape);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.draw(sprite);
        window.display();




    }

    return 0;
}
