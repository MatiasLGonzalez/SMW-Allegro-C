#include"header.h"

bool keys[4] = { false, false, false, false };


ALLEGRO_DISPLAY* display = NULL;//Pointer to main display window
ALLEGRO_FONT* font11 = NULL;//Pointers to fonts
ALLEGRO_PATH* main_directory = NULL, * font_directory = NULL, * sprites_directory = NULL;//Pointers to paths
ALLEGRO_BITMAP* mario_sprite = NULL, * characters = NULL, * buffer = NULL,* backgrounds = NULL, * background_1 = NULL,* level = NULL;//Pointer to bitmaps
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_EVENT ev;
ALLEGRO_TIMER* timer = NULL;

int width = 0, height = 0;// Width and Height of actual monitor
int w = 0, h = 0, tw = 0, th = 0;//Width and height of window

const int FPS = 60;

int GROUND = 191 - 20;

Mario mario;
camera Camera;

bool done = false, redraw = false;

int main(void)
{
	//Initialization of variables and loading of resources stage
	if (!al_init())//Initialization of the allegro system
	{
		al_show_native_message_box(NULL, "Error al inicializar Allegro.", "Error al inicializar Allegro.", "Error al inicializar Allegro.", "OK?", 0);
		return -1;
	}
	

	main_directory = al_get_standard_path(ALLEGRO_RESOURCES_PATH);//Creation of main game directory
	get_desktop_resolution(0, &width, &height);//Desktop resolution 
	w = width * 0.75 * 0.75;//Width of window resolution (4:3) at 75% of desktop resolution
	h = height * 0.75;//Height of window resolution (4:3) at 75% of desktop resolution
	printf("%d %d\n", w , h);
	display = al_create_display(w, h);//Creation of display
	tw = 256;//True width of backbuffer
	th = 224;//True height of backbuffer
	
	float sx = w / (float)tw;
	float sy = h / (float)th;

	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_scale_transform(&trans, sx, sy);
	al_use_transform(&trans);

	if (!display)//Check of correct creation of the display
	{
		al_show_native_message_box(NULL, "Error al inicializar la ventana.", "Error al inicializar la ventana.", "Error al inicializar la ventana.", "OK?", 0);
		return -2;
	}

	if (!al_install_keyboard())
	{
		al_show_native_message_box(NULL, "Error al iniciar el teclado.", "Error al iniciar el teclado.", "Error al iniciar el teclado.", "OK?", 0);
		return -8;
	}

	if (!al_init_primitives_addon())
	{
		al_show_native_message_box(NULL, "Error al iniciar addon de primitivas.", "Error al iniciar addon de primitivas.", "Error al iniciar addon de primitivas.", "OK?", 0);
		return -7;
	}

	if (!al_init_font_addon())//Initialization of the allegro font addon
	{
		al_show_native_message_box(NULL, "Error al inicializar addon de fuentes.", "Error al inicializar fuentes.", "Error al inicializar fuentes.", "OK?", 0);
		return -3;
	}
	
	if (!al_init_ttf_addon())//Initialization of the allegro TTF addon
	{
		al_show_native_message_box(NULL, "Error al inicializar addon ttf.", "Error al inicializar ttf.", "Error al inicializar ttf.", "OK?", 0);
		return -4;
	}

	if (!al_init_image_addon())//Initialization of the allegro image addon
	{
		al_show_native_message_box(NULL, "Error al inicializar addon de imagen.", "Error al inicializar imagen.", "Error al inicializar imagen.", "OK?", 0);
		return -5;
	}
	
	font_directory = al_get_standard_path(ALLEGRO_RESOURCES_PATH);//Giving the font directory pointer the base directory of the game
	al_append_path_component(font_directory, "fonts");//Appending the "fonts" folder to the font directory pointer 
	al_set_path_filename(font_directory, "Super-Mario-World.ttf");//Setting the filename for the corresponding font to be load
	font11 = al_load_ttf_font(al_path_cstr(font_directory, '/' ), 11, 0);//Loading main font size 11

	if (!font11)//Check of successful font loading
	{
		al_show_native_message_box(NULL, "Error al cargar fuentes.", "Error al cargar fuentes.", "Error al cargar fuentes.", "OK?", 0);
		return -6;
	}
	

	

	sprites_directory = al_get_standard_path(ALLEGRO_RESOURCES_PATH);//Giving the sprites directory pointer the base directory of the game
	al_append_path_component(sprites_directory, "sprites");//Appending the "fonts" folder to the font directory pointer 
	al_set_path_filename(sprites_directory, "characters.png");//Setting the filename for the corresponding font to be load
	characters = al_load_bitmap(al_path_cstr(sprites_directory, '/'));

	sprites_directory = al_get_standard_path(ALLEGRO_RESOURCES_PATH);//Giving the sprites directory pointer the base directory of the game
	al_append_path_component(sprites_directory, "sprites");//Appending the "fonts" folder to the font directory pointer 
	al_set_path_filename(sprites_directory, "backgrounds.png");//Setting the filename for the corresponding font to be load
	backgrounds = al_load_bitmap(al_path_cstr(sprites_directory, '/'));

	sprites_directory = al_get_standard_path(ALLEGRO_RESOURCES_PATH);//Giving the sprites directory pointer the base directory of the game
	al_append_path_component(sprites_directory, "sprites");//Appending the "fonts" folder to the font directory pointer 
	al_set_path_filename(sprites_directory, "level.png");//Setting the filename for the corresponding font to be load
	level = al_load_bitmap(al_path_cstr(sprites_directory, '/'));
	if (!characters || !backgrounds)
	{
		printf("Characters or background null");
		system("pause");
	}

	mario_sprite = al_create_sub_bitmap(characters, 2, 14, 14, 20);
	background_1 = al_create_sub_bitmap(backgrounds, 2, 631, tw, th);
	al_convert_mask_to_alpha(mario_sprite, al_map_rgb(0, 64, 64));


	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));


	Camera.x = 0;
	Camera.y = 193;
	start_mario(&mario, 0, GROUND, 5, 0, mario_sprite, w, h);
	al_start_timer(timer);
	//Main game loop
	while (!done)
	{
		
		al_wait_for_event(event_queue, &ev);
		
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			move_mario(&mario, keys, &Camera);

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				keys[LEFT] = true;
			}else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				keys[RIGHT] = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
			{
				keys[UP] = true;
				if (mario.vy <= 0 && mario.pos_y == GROUND)
				{
					mario.vy = 5.81333;
					mario.ay = 0.376777;
				}
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
			{
				keys[DOWN] = true;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				keys[LEFT] = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				keys[RIGHT] = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
			{
				keys[UP] = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
			{
				keys[DOWN] = false;
			}
		}





		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			//draw phase
			al_draw_textf(font11, al_map_rgb(255, 255, 255), tw / 2, th / 2, ALLEGRO_ALIGN_CENTRE, "Hello World!");
			drawBackground(Camera, level, background_1);
			drawMario(&mario);

			al_flip_display();
		}
	}
	
	

	al_destroy_display(display);
	al_uninstall_keyboard();
	
	return 0;
}

