#include <cstdlib>
#include <crtdbg.h>
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

#define WIDHT 800
#define HEIGHT 600

#define BLACK {0,0,0}
#define WHITE {255,255,255}
#define RED {255,0,0}
#define LIME {0,255,0}
#define BLUE {0,0,255}
#define YELLOW {255,255,0}
#define AQUA {0,255,255}
#define MAGENTA {255,0,255}
#define SILVER {192,192,192}
#define GRAY {128,128,128}
#define MAROON {128,0,0}
#define OLIVE {128,128,0}
#define GREEN {0,128,0}
#define PURPLE {128, 0, 128}
#define TEAL {0,128,128}
#define NAVY {0,0,128}

struct color {
	int r;
	int g;
	int b;
}; 

std::vector<color> colors = { BLACK, WHITE, RED, LIME, BLUE, YELLOW, AQUA, MAGENTA, SILVER, GRAY, MAROON, OLIVE, GREEN, PURPLE, TEAL, NAVY };
int table_size = 60;
int cell_size = 600 / table_size;
color background = BLACK;
color squarecolor = WHITE;

int neighbours(std::vector<int> vec, int i);
void INIT(SDL_Renderer*& render, SDL_Window*& window);
void drawSquare(SDL_Renderer*& render, int x, int y, int option);
void simulation(SDL_Renderer*& render, std::vector<int>& vec, std::vector<int>& vec_help);
void show_play_button(SDL_Renderer*& render, SDL_Texture*& button, int option);
void show_pause_button(SDL_Renderer*& render, SDL_Texture*& button, int option);
void show_quit_button(SDL_Renderer*& render, SDL_Texture*& button);
void show_option_button(SDL_Renderer*& render, SDL_Texture*& button);
void show_table_options(SDL_Renderer*& render, SDL_Texture*& button);
void show_option_properties(SDL_Renderer*& render, SDL_Texture*& texts, SDL_Texture*& button);
void Show_Buttons(SDL_Renderer*& render, SDL_Texture*& buttons);
void Init_table(SDL_Renderer*& render, std::vector<int>& vec, std::vector<int>& vec_help);

int main(int argc, char** argv) {

	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
	INIT(render, window);

	SDL_Texture* buttons = IMG_LoadTexture(render, "buttons.png");
	SDL_Texture* texts = IMG_LoadTexture(render, "text.png");

	Show_Buttons(render, buttons);

	std::vector<int> vec;
	std::vector<int> vec_help;
	Init_table(render, vec, vec_help);
	
	SDL_Event event;
	bool quit = false;
	bool start = false;
	bool pause = false;
	bool option = false;
	bool motion = !false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEMOTION:
				if (motion && event.motion.x <= 599) {
					drawSquare(render, (event.motion.x / cell_size), (event.motion.y / cell_size), 0);
					SDL_RenderPresent(render);
					vec[event.motion.x / cell_size % table_size + event.motion.y / cell_size * table_size] = 1;
					vec_help[event.motion.x / cell_size % table_size + event.motion.y / cell_size * table_size] = 1;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					//600x600 table
					if (event.button.x <= 599) {
						drawSquare(render, (event.button.x / cell_size), (event.button.y / cell_size), 0);
						SDL_RenderPresent(render);
						vec[event.button.x / cell_size % table_size + event.button.y / cell_size * table_size] = 1;
						vec_help[event.button.x / cell_size % table_size + event.button.y / cell_size * table_size] = 1;
					}
					//If you click on play button
					else if (!start && event.button.x >= 635 && event.button.x <= 765 && event.button.y >= 375 && event.button.y <= 440) {
						if (pause) {
							show_pause_button(render, buttons, 0);
						}
						show_play_button(render, buttons, 1);
						start = true;
						pause = false;
						motion = false;
					}
					//If you click on pause button
					else if (!pause && event.button.x >= 635 && event.button.x <= 765 && event.button.y >= 450 && event.button.y <= 515) {
						if (start) {
							show_play_button(render, buttons, 0);
						}
						show_pause_button(render, buttons, 1);
						start = false;
						pause = true;
					}
					//If you click on quit button
					else if (!quit && event.button.x >= 635 && event.button.x <= 765 && event.button.y >= 525 && event.button.y <= 590) {
						quit = true;
						start = false;
						pause = false;
					}
					//If you click on option button
					else if (event.button.x >= 635 && event.button.x <= 765 && event.button.y >= 10 && event.button.y <= 75) {
						if (!option) {
							show_option_properties(render, texts, buttons);
							SDL_RenderPresent(render);
							option = true;
						}
						else {
							SDL_Rect clear_option = { 620,80,150,200 };
							SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
							SDL_RenderFillRect(render, &clear_option);
							SDL_RenderPresent(render);
							option = false;
						}
					}
					//Background color
					else if (option && event.button.x >= 635 && event.button.x <= 750 && event.button.y >= 105 && event.button.y <= 130) {
						bool l = false;
						int c;
						for (int i = 0; i < colors.size() && !l; i++) {
							int x = 635 + i % 8 * 15;
							int y = 105 + i / 8 * 15;
							l = l || (event.button.x >= x && event.button.x <= x + 10 && event.button.y >= y && event.button.y <= y + 10);
							c = i;
						}
						if (l) {
							background = colors[c];
							for (int i = 0; i < vec.size(); i++) {
								if (vec[i] == 0) {
									drawSquare(render, i % table_size , i / table_size, 1);
								}
							}
							SDL_RenderPresent(render);
						}
					}
					//Square color
					else if (option && event.button.x >= 635 && event.button.x <= 750 && event.button.y >= 160 && event.button.y <= 185) {
						bool l = false;
						int c;
						for (int i = 0; i < colors.size() && !l; i++) {
							int x = 635 + i % 8 * 15;
							int y = 160 + i / 8 * 15;
							l = l || (event.button.x >= x && event.button.x <= x + 10 && event.button.y >= y && event.button.y <= y + 10);
							c = i;
						}
						if (l) {
							squarecolor = colors[c];
							for (int i = 0; i < vec.size(); i++) {
								if (vec[i] == 1) {
									drawSquare(render, i % table_size, i / table_size, 0);
								}
							}
							SDL_RenderPresent(render);
						}
					}
					else if (option && !start && !pause && event.button.x >= 635 && event.button.x <= 750 && event.button.y >= 213 && event.button.y <= 238) {
						if (table_size != 15 && event.button.x >= 635 && event.button.x <= 660) { table_size = 15; cell_size = 600 / table_size; show_table_options(render, buttons); Init_table(render, vec, vec_help); }
						else if (table_size != 30 && event.button.x >= 665 && event.button.x <= 690) { table_size = 30; cell_size = 600 / table_size; show_table_options(render, buttons); Init_table(render, vec, vec_help);}
						else if (table_size != 60 && event.button.x >= 695 && event.button.x <= 720) { table_size = 60; cell_size = 600 / table_size; show_table_options(render, buttons); Init_table(render, vec, vec_help);}
						else if (table_size != 120 && event.button.x >= 725 && event.button.x <= 750) { table_size = 120; cell_size = 600 / table_size; show_table_options(render, buttons); Init_table(render, vec, vec_help);}

						SDL_RenderPresent(render);
					}
				}
				break;
			}
		}
		if (start) {
			simulation(render, vec, vec_help);
		}
	}
	vec.~vector();
	vec_help.~vector();
	colors.~vector();
	SDL_DestroyTexture(buttons);
	SDL_DestroyTexture(texts);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();
	return 0;
}

//This function inits the renderer and the window
void INIT(SDL_Renderer*& render, SDL_Window*& window) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDHT, HEIGHT, 2);
	if (window == nullptr) { std::cout << "Window nem hozhato letre!" << std::endl; SDL_Quit();  exit(1); }

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == nullptr) { std::cout << "Renderer nem hozhato letre!" << std::endl; SDL_DestroyWindow(window); SDL_Quit();  exit(1); }
}

// This function need x and y coordinate and it will display a coloured square
//Option=0 -> Death cell color
//Option=1 -> Living cell color
void drawSquare(SDL_Renderer * &render, int x, int y, int option) {
	option == 1 ? SDL_SetRenderDrawColor(render, background.r, background.g, background.b, 255) : SDL_SetRenderDrawColor(render, squarecolor.r, squarecolor.g, squarecolor.b, 255);
	SDL_Rect rectangle;
	rectangle.x = x * cell_size;
	rectangle.y = y * cell_size;
	rectangle.w = cell_size;
	rectangle.h = cell_size;
	SDL_RenderFillRect(render, &rectangle);
}

//This function counts the neighbours of an element of the vector
int neighbours(std::vector<int> vec, int i) {
	int c = 0;
	int x = i % table_size;
	int y = i / table_size;
	if (x + 1 < table_size && vec[i + 1] == 1) {
		c++;
	}
	if (x - 1 >= 0 && vec[i - 1] == 1) {
		c++;
	}
	if (y + 1 < table_size && vec[i + table_size] == 1) {
		c++;
	}
	if (y + 1 < table_size && x + 1 < table_size && vec[i + table_size + 1] == 1) {
		c++;
	}
	if (y + 1 < table_size && x - 1 >= 0 && vec[i + table_size - 1] == 1) {
		c++;
	}
	if (y - 1 >= 0 && vec[i - table_size] == 1) {
		c++;
	}
	if (y - 1 >= 0 && x + 1 < table_size && vec[i - table_size + 1] == 1) {
		c++;
	}
	if (y - 1 >= 0 && x - 1 >= 0 && vec[i - table_size - 1] == 1) {
		c++;
	}
	return c;
}

//This function is the algorithm of game of life
void simulation(SDL_Renderer*& render, std::vector<int>& vec, std::vector<int>& vec_help) {
	for (int i = 0; i < vec.size(); i++) {
		int n = neighbours(vec, i);
		if (n == 2) {
			continue;
		}
		if (n == 3 || vec[i] == 0) {
			drawSquare(render, i % table_size, i / table_size, 0);
			vec_help[i] = 1;
		}
		if (n < 2 || n > 3) {
			drawSquare(render, i % table_size, i / table_size, 1);
			vec_help[i] = 0;
		}
	}
	vec = vec_help;
	SDL_RenderPresent(render);
}

void show_play_button(SDL_Renderer*& render, SDL_Texture*& button, int option) {
	SDL_Rect play_button_img;
	if (option == 0) { //Default color
		play_button_img = { 0, 75, 50, 25 };
	}
	else {//Grey color
		play_button_img = { 0, 100, 50, 25 };
	}
	SDL_Rect play_button_img_pos = { 635, 375, 130, 65 };
	SDL_RenderCopy(render, button, &play_button_img, &play_button_img_pos);
	SDL_RenderPresent(render);
}

void show_pause_button(SDL_Renderer*& render, SDL_Texture*& button, int option) {
	SDL_Rect pause_button_img;
	if (option == 0) { //Default color
		pause_button_img = { 0, 25, 50, 25 };
	}
	else {//Grey color
		pause_button_img = { 0, 50, 50, 25 };
	}
	SDL_Rect pause_button_img_pos = { 635, 450, 130, 65 };
	SDL_RenderCopy(render, button, &pause_button_img, &pause_button_img_pos);
	SDL_RenderPresent(render);
}

void show_quit_button(SDL_Renderer*& render, SDL_Texture*& button) {
	SDL_Rect quit_button_img = { 0, 125, 50, 25 };
	SDL_Rect quit_button_img_pos = { 635, 525, 130, 65 };
	SDL_RenderCopy(render, button, &quit_button_img, &quit_button_img_pos);
	SDL_RenderPresent(render);
}

void show_option_button(SDL_Renderer*& render, SDL_Texture*& button) {
	SDL_Rect quit_button_img = { 0, 0, 50, 25 };
	SDL_Rect quit_button_img_pos = { 635, 10, 130, 65 };
	SDL_RenderCopy(render, button, &quit_button_img, &quit_button_img_pos);
	SDL_RenderPresent(render);
}

void show_table_options(SDL_Renderer*& render, SDL_Texture*& button) {
	SDL_Rect size_rect;
	SDL_Rect size_rect_pos;
	//15
	size_rect_pos = { 635, 213, 25, 25 };
	table_size == 15 ? size_rect = { 75,0,25,25 } : size_rect = { 50,0,25,25 };
	SDL_RenderCopy(render, button, &size_rect, &size_rect_pos);

	//30
	size_rect_pos = { 665, 213, 25, 25 };
	table_size == 30 ? size_rect = { 75,25,25,25 } : size_rect = { 50,25,25,25 };
	SDL_RenderCopy(render, button, &size_rect, &size_rect_pos);

	//60
	size_rect_pos = { 695, 213, 25, 25 };
	table_size == 60 ? size_rect = { 75,50,25,25 } : size_rect = { 50,50,25,25 };
	SDL_RenderCopy(render, button, &size_rect, &size_rect_pos);

	//60
	size_rect_pos = { 725, 213, 25, 25 };
	table_size == 120 ? size_rect = { 75,75,25,25 } : size_rect = { 50,75,25,25 };
	SDL_RenderCopy(render, button, &size_rect, &size_rect_pos);
}

void show_option_properties(SDL_Renderer*& render, SDL_Texture*& texts, SDL_Texture*& button) {
	SDL_Rect option_text;
	SDL_Rect option_text_pos;
	SDL_Rect color_rect;

	//Background text
	option_text = { 10, 20, 340, 40 };
	option_text_pos = { 635, 85, 120, 15 };
	SDL_RenderCopy(render, texts, &option_text, &option_text_pos);

	//Background colors
	for (int i = 0; i < colors.size(); i++) {
		SDL_SetRenderDrawColor(render, colors[i].r, colors[i].g, colors[i].b, 255);
		color_rect = { 635 + i % 8 * 15 , 105 + i / 8 * 15,10,10 };
		SDL_RenderFillRect(render, &color_rect);
	}

	//Square text
	option_text = { 10, 75, 250, 40 };
	option_text_pos = { 635, 140, 95, 14 };
	SDL_RenderCopy(render, texts, &option_text, &option_text_pos);

	// Square colors
	for (int i = 0; i < colors.size(); i++) {
		SDL_SetRenderDrawColor(render, colors[i].r, colors[i].g, colors[i].b, 255);
		color_rect = { 635 + i % 8 * 15 , 160 + i / 8 * 15,10,10 };
		SDL_RenderFillRect(render, &color_rect);
	}

	//Table size text
	option_text = { 10, 178, 190, 32 };
	option_text_pos = { 635, 195, 75, 12 };
	SDL_RenderCopy(render, texts, &option_text, &option_text_pos);

	//Show the table size options
	show_table_options(render, button);

}

void Show_Buttons(SDL_Renderer*& render, SDL_Texture*& buttons) {
	SDL_Rect right_rect = { 600,0,200,600 };
	SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
	SDL_RenderFillRect(render, &right_rect);

	show_play_button(render, buttons, 0);
	show_pause_button(render, buttons, 0);
	show_quit_button(render, buttons);
	show_option_button(render, buttons);
}

void Init_table(SDL_Renderer*& render, std::vector<int>& vec, std::vector<int>& vec_help) {
	SDL_Rect left_rect = { 0,0,600,600 };
	SDL_SetRenderDrawColor(render, background.r, background.g, background.b, 255);
	SDL_RenderFillRect(render, &left_rect);
	vec.clear();
	vec.resize(table_size * table_size);
	vec_help = vec;
}