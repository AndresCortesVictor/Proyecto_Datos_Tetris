#include <SFML/Graphics.hpp>
#include <optional>
using namespace sf;

int main(int argc, char *argv[]) {
		RenderWindow w(VideoMode({640, 480}), "Tetris");
		RectangleShape celda(Vector2f(20.f, 20.f));
		celda.setPosition(Vector2f(100.f, 200.f));
		celda.setFillColor(Color::Red);

		while (w.isOpen()) {
			while (auto e = w.pollEvent()) {
				if (e->is<Event::Closed>()) {
					w.close();
				}
				if (e->is<Event::KeyPressed>()) {
					auto kp = e->getIf<Event::KeyPressed>();
					if (kp->code == Keyboard::Key::Escape) {
						w.close();
					}
					if (kp->code == Keyboard::Key::Left) {
						celda.move(Vector2f(-5.f, 0.f));
					}
				}
			}

			w.clear();
			w.draw(celda);
			w.display();
		}
}
