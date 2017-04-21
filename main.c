//2016-CS Project

#include <allegro.h>
#include <stdio.h>
#include <time.h>
#include "Definitions.h"
int main(void) {
	int depth, res;
	/*init-install fonksiyonlari*/
	allegro_init();
	if (allegro_init() != 0) printf("allegro kurulamadi.. ");
	install_keyboard();
	if (install_keyboard() != 0) printf("keyboard kurulmadi.. ");
	install_timer();
	if (install_timer() != 0) printf("timer kurulmadi.. ");
	install_mouse();
	if (install_mouse() != 0) printf("mouse kurulmadi.. ");
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT, "A");
	LOCK_FUNCTION(downTimer);
	LOCK_VARIABLE(controlTicks);
	LOCK_FUNCTION(controlTimer);
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 900,680, 0, 0);             //ekran yaratma										   
	SAMPLE * sound;                   
	sound = load_sample("tetris.wav");								  //müzik yükle
	play_sample(sound, 255, 128, 1000, true);						  //müzik başla
	BITMAP *menuKatmani = create_bitmap(900, 680);
	BITMAP *menu = load_bitmap("menu.bmp", NULL);
	BITMAP *play = load_bitmap("play.bmp", NULL);
	BITMAP *exit = load_bitmap("exit.bmp", NULL);
	BITMAP *cursor = load_bitmap("cursor.bmp", NULL);
	
	show_mouse(screen);
	while (!key[KEY_ESC]) {
		blit(menu, menuKatmani, 0, 0, 0, 0, 900, 680);
		blit(play, menuKatmani, 0, 0, 350, 290, 150, 50);
		blit(exit, menuKatmani, 0, 0, 350, 340, 150, 50);
		blit(menuKatmani, screen, 0, 0, 0, 0, 900, 680);
		clear_bitmap(menuKatmani);
		if (mouse_x > 350 && mouse_x < 500 && mouse_y > 290 && mouse_y < 340 && (mouse_b & 1))
			break;
		else if (mouse_x > 350 && mouse_x < 500 && mouse_y > 340 && mouse_y < 400 && (mouse_b & 1)) {
			return 0;
		}
	}
	install_int_ex(inis_sure_fonk, SECS_TO_TIMER(1));   
	install_int_ex(zaman_kontrol, MSEC_TO_TIMER(100));  //tuşlara basarken değişen zaman kontrolü
	oyunu_yukle();		   //oyunu yükle
	line(arkaplan,170,0,170,900, makecol(255,255,255));								  //sol çizgi
	line(arkaplan,675, 0,675, 900, makecol(255, 255, 255));						      //sağ çizgi
	/
while (!key[KEY_ESC]){
			block_kontrol();
			ciz();
			oyun_sonu_kontrol();
		}
	stop_sample(sound);  //müzik durdur
	/*yok etme fonksiyonlari*/
	destroy_sample(sound);
	destroy_bitmap(buffer);
	destroy_bitmap(arkaplan);
	destroy_bitmap(block_bitmap);

	return 0;
}
END_OF_MAIN();
