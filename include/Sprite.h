#pragma once

class Sprite
{
	public:
		Sprite ();
		~Sprite ();
		void draw ();
		void init (int x, int y, int width, int height);
	private:
		int sX, sY, sWidth, sHeight;
};
