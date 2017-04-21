#include <allegro.h>
#include <time.h>
							/*
*************************
  BLOK-MATRIS
  13   14  15  4      T
  5    4   14  13     S
  3    4   14  15     Z
  4    14  24  25     L
  4    14  24  23     7
  4    5   14  15     Kare   
  4    14  24   34    L2
*/

void init();
void zaman_kontrol();
void inis_sure_fonk();
void oyunu_yukle();
void block_hareket();
void block_kontrol();
void ciz();
void block_yenile();
void block_dondur(int dondurmeSayisi);
void block_sil();
void sonrakiBlok();
void oyun_sonu_kontrol();
void block_seklini_belirle();
int skor = 0, dondurmeSayisi = 0, dondurme = 0, sonraki_block = 0;
int x = 0; 
BITMAP *buffer;  
BITMAP *arkaplan;
BITMAP *block_bitmap;
const int genislik = 10;
const int yukseklik = 14;
unsigned int giris_sure = 0;
unsigned int inis_sure = 0;
int block[7][4];
int oyunAlani[yukseklik][genislik]={{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 }, 
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0 } };
int gecici_block[4][4] ={{ 0,0,0,0 },
					   	 { 0,0,0,0 },
						 { 0,0,0,0 },
						 { 0,0,0,0 } };
/*Fonksiyonlar*/
void zaman_kontrol() {
	giris_sure++;
}
void inis_sure_fonk() {
	inis_sure++;
} 
void oyunu_yukle(){ 
	srand(time(NULL));
	buffer = create_bitmap(900, 680);						  //buffer yarat
	arkaplan = load_bitmap("background.bmp", NULL);           //arka plan yükle
	block_bitmap = load_bitmap("block.bmp", NULL);            //blok resmi                 
	block_yenile();
}   

/*Hareket kontrol fonksiyonu*/
void block_hareket(){
	while (inis_sure > 0){
		int satir = 0, sutun = 0,i;
		bool hareket = true;
		for (i = 0; i <= 3; i++)	{ 
			satir = (block[x][i] / genislik);
			sutun = (block[x][i] % genislik);
			if (satir > 0) 
				 oyunAlani[satir - 1][sutun] = 0; 
		}
		for (i = 0; i <= 3; i++)	{
			satir = (block[x][i] / genislik);
			sutun = (block[x][i] % genislik);
			if (oyunAlani[satir][sutun] == 1 || satir >= yukseklik)	{ //yuksekligi gecerse ya da blok varsa durdur 
				hareket = false;
				break;
			}
		}
		if (!hareket)  {
			for (i = 0; i <= 3; i++){
				satir = (block[x][i] / genislik);
				sutun = (block[x][i] % genislik);
				if(satir >0)
					oyunAlani[satir - 1][sutun] = 1;//blok durduðunda olduğu yeri 1 olarak belirle
			}											 	
			block_sil();       
			block_yenile();
			dondurme = 0;
			return;
		} 


	  for (i = 0; i <= 3; i++) {   //tuşa basılmazsa indirme işlemini yapar
			satir = (block[x][i] / genislik);
			sutun = (block[x][i] % genislik);
			oyunAlani[satir][sutun] = 1;
			satir++;
			block[x][i] = (satir * genislik + sutun);
		}
		inis_sure--;
	}
}
void block_kontrol() {     //tip kontrol 
	while (giris_sure > 0) {
		int satir = 0, sutun = 0,i;
		bool  kUp = false, kRight = false, kLeft = false, kDown = false;
		bool  cUp = true, cRight = true, cLeft = true, cDown = true;
		if (key[KEY_RIGHT]) 
			kRight = true;
		if (kRight){

			block_seklini_belirle();

			for (i = 0; i <= 3; i++) //duvara girmeyi engelle,durdur
			{
				satir = (block[x][i] / genislik) - 1;
				sutun = (block[x][i] % genislik);
				if (oyunAlani[satir][sutun + 1] == 1 || sutun >= genislik - 1 || satir <= 0) cRight = false;
			}
			if (cRight){ 
				for (i = 0; i <= 3; i++)
				{
					block[x][i]++;
					satir = (block[x][i] / genislik) - 1;
					sutun = (block[x][i] % genislik);
					oyunAlani[satir][sutun] = 1;
				}
			}
		}
		if (key[KEY_LEFT]) kLeft = true;
		if (kLeft)  {
			
			block_seklini_belirle();

			for (i = 0; i <= 3; i++){
				satir = (block[x][i] / genislik) - 1;
				sutun = (block[x][i] % genislik);
				if (oyunAlani[satir][sutun - 1] == 1 || sutun <= 0) cLeft = false;
			}
			if (cLeft)	{
				for (i = 0; i <= 3; i++){  //sola kaydýr
					block[x][i]--;
					satir = (block[x][i] / genislik) - 1;
					sutun = (block[x][i] % genislik);
					if (satir >= 0)
						oyunAlani[satir][sutun] = 1;
				}
			}
		}
		if (key[KEY_UP]) kUp = true;
		if (kUp){           //block nerde diye matriste belirle

			block_seklini_belirle();

			for (i = 0; i <= 3; i++)	{   
				satir = (block[x][i] / genislik) - 1;
				sutun = (block[x][i] % genislik);
				if (oyunAlani[satir + 1][sutun] == 1 || sutun <= 0 && i == 1 || sutun >= genislik - 1 && i == 1) //düz çubuk dönme kontrolü
				{
					cUp = false;
				}
				if (x == 6 && sutun >= genislik - 2 && i == 2 && dondurme < 6) cUp = false;
			}
			if (cUp)	{ //cUp true ise dönme iþlemini yap
				block_dondur(dondurmeSayisi);    //blok döndür
				for (i = 0; i <= 3; i++){
					satir = (block[x][i] / genislik) - 1;
					sutun = (block[x][i] % genislik);
					if (satir >= 0)oyunAlani[satir][sutun] = 1;
				}
			}
		}
		if (key[KEY_DOWN]) kDown = true;
		if (kDown){ 
			block_seklini_belirle();
				for (i = 0; i <= 3; i++){
					satir = (block[x][i] / genislik) - 1;
					sutun = (block[x][i] % genislik);
					if (oyunAlani[satir + 1][sutun] == 1 || satir >= yukseklik - 1) cDown = false;
				}
				if (cDown){
					for (i = 0; i <= 3; i++)
					{
						block[x][i] += 10;
						satir = (block[x][i] / genislik) - 1;
						sutun = (block[x][i] % genislik);
						oyunAlani[satir][sutun] = 1;
					}
				}
		}
			if (!cRight || !cLeft || !cDown || !cUp) {
				for (i = 0; i <= 3; i++)
				{
					satir = (block[x][i] / genislik) - 1;
					sutun = (block[x][i] % genislik);
					if (satir >= 0) oyunAlani[satir][sutun] = 1;
				}
			}
		dondurmeSayisi = x + dondurme;
	    giris_sure--;
	}
	textprintf_ex(screen, font, 750, 500, makecol(255, 100, 200), -1, "Puan: %d", skor);
	block_hareket();
}
/*cizim Fonksiyonu*/
void ciz() {
	int satir, sutun;
	blit(arkaplan, buffer, 0, 0, 0, 0, 900, 680);
	for (satir = 0; satir <= yukseklik - 1; satir++) {    
		for (sutun = 0; sutun <= genislik - 1; sutun++) {
			if (oyunAlani[satir][sutun] == 1)
				blit(block_bitmap, buffer, 0, 0, (50 * sutun) + 175, satir * 50, 50, 50);
		}
	}
	for (satir = 0; satir <= 4; satir++) {    
		for (sutun = 0; sutun <= 3; sutun++) {
			if (gecici_block[satir][sutun] == 1)
				blit(block_bitmap, buffer, 0, 0, (50 * sutun) + 700, (satir * 50) + 225, 50, 50);
		}
	}
	blit(buffer, screen, 0, 0, 0, 0, 1024, 768);
	textprintf_ex(screen, font, 750, 500, makecol(255, 100, 200), -1, "Puan: %d", skor);
}
void block_yenile(){    //blok şekillerini ilk hale getir
	x = sonraki_block;
	block[0][0] = 13;
	block[0][1] = 14;
	block[0][2] = 15;
	block[0][3] = 4;
	
	block[1][0] = 5;
	block[1][1] = 4;
	block[1][2] = 14;
	block[1][3] = 13;
	
	block[2][0] = 3;
	block[2][1] = 4;
	block[2][2] = 14;
	block[2][3] = 15;
	
	block[3][0] = 4;
	block[3][1] = 14;
	block[3][2] = 24;
	block[3][3] = 25;
	
	block[4][0] = 4;
	block[4][1] = 14;
	block[4][2] = 24;
	block[4][3] = 23;
	
	block[5][0] = 4;
	block[5][1] = 5;
	block[5][2] = 14;
	block[5][3] = 15;
	
	block[6][0] = 4;
	block[6][1] = 14;
	block[6][2] = 24;
	block[6][3] = 34;

	sonrakiBlok();
}
void block_dondur(int dondurmeSayisi){	
	int satir = 0, sutun = 0,i;
	for (i = 0; i <= 3; i++){
		satir = (block[x][i] / genislik) - 1;
		sutun = (block[x][i] % genislik);
		if (satir >= 0)oyunAlaný[satir][sutun] = 0;
	}
	switch (dondurmeSayisi)   {
		case 0:
			block[0][0] -= 9;
			block[0][1] += 0;
			block[0][2] += 9;
			block[0][3] += 11;
			dondurme += 7;
			break;
		case 1: 
			block[1][0] -= 11;
			block[1][1] += 0;
			block[1][2] -= 9;
			block[1][3] += 2;
			dondurme += 9;
			break;
		case 2:
			block[2][0] -= 9;
			block[2][1] -= 0;
			block[2][2] -= 1;
			block[2][3] -= 12;
			dondurme += 9;
			break;
		case 3:
			block[3][0] += 11;
			block[3][1] -= 0;
			block[3][2] -= 11;
			block[3][3] -= 2;
			dondurme += 9;
			break;
		case 4:
			block[4][0] += 11;
			block[4][1] += 0;
			block[4][2] -= 11;
			block[4][3] -= 20;
			dondurme += 11;
			break;
		case 5:
			dondurme = 0;
			break;
		case 6:
			block[6][0] += 9;
			block[6][1] -= 0;
			block[6][2] -= 9;
			block[6][3] -= 18;
			dondurme += 12;
			break;
		case 7:
			block[0][0] += 11;
			block[0][1] += 0;
			block[0][2] -= 11;
			block[0][3] += 9;
			dondurme += 1;
			break;
		case 8:
			block[0][0] += 9;
			block[0][1] += 0;
			block[0][2] -= 9;
			block[0][3] -= 11;
			dondurme += 1;
			break;
		case 9:
			block[0][0] -= 11;
			block[0][1] += 0;
			block[0][2] += 11;
			block[0][3] -= 9;
			dondurme -= 9;
			break;
		case 10:
			block[1][0] += 11;
			block[1][1] += 0;
			block[1][2] += 9;
			block[1][3] -= 2;
			dondurme -= 9;
			break;
		case 11:
			block[2][0] += 9;
			block[2][1] += 0;
			block[2][2] += 1;
			block[2][3] += 12;
			dondurme -= 9;
			break;
		case 12:
			block[3][0] += 9;
			block[3][1] -= 0;
			block[3][2] -= 9;
			block[3][3] -= 20;
			dondurme += 1;
			break;
		case 13:
			block[3][0] -= 11;
			block[3][1] -= 0;
			block[3][2] += 11;
			block[3][3] += 2;
			dondurme += 1;
			break;
		case 14:
			block[3][0] -= 9;
			block[3][1] -= 0;
			block[3][2] += 9;
			block[3][3] += 20;
			dondurme -= 11;
			break;
		case 15:
			block[4][0] += 9;
			block[4][1] += 0;
			block[4][2] -= 9;
			block[4][3] += 2;
			dondurme += 1;
			break;
		case 16:
			block[4][0] -= 9;
			block[4][1] += 0;
			block[4][2] += 9;
			block[4][3] += 20;
			dondurme += 1;
			break;
		case 17:
			block[4][0] -= 11;
			block[4][1] += 0;
			block[4][2] += 11;
			block[4][3] -= 2;
			dondurme -= 13;
			break;
		case 18:
			block[6][0] -= 9;
			block[6][1] += 0;
			block[6][2] += 9;
			block[6][3] += 18;
			dondurme -= 12;
			break;
		}
}

void block_sil()
{
	int satirNumarasi = 0, i = 0, c;
	int satir, sutun;
	static int silinen_block[4];
	bool kaydir = false;
	for (i = 0; i <= 4; i++) {
		silinen_block[i] = 0;
	} //saðdaki blocku sil
	i = 0;
	for (satir = 0; satir <= yukseklik - 1; satir++) {
		for (sutun = 0; sutun <= genislik - 1; sutun++) {
			satirNumarasi = satirNumarasi + oyunAlaný[satir][sutun];
			if (satirNumarasi >= 10) {
				silinen_block[i] = satir;
				satirNumarasi = 0;
				if (i < 4) i++;
				kaydýr = true;
			}
		}
		if (satirNumarasi < 10)
			satirNumarasi = 0;
	}
	if (kaydýr) {
		for (i = 0; i <= 3; i++) {
			for (satir = silinen_block[i]; satir >0; satir--) {
				for (sutun = 0; sutun <= genislik - 1; sutun++) {
					if (satir > 0) {
						oyunAlaný[satir][sutun] = oyunAlaný[satir - 1][sutun];
					}
				}
			}
		}
		skor += 100;
	}

}
void sonrakiBlok(){
	int satir = 0, sutun = 0;
	int i;
	for (satir = 0; satir <= 3; satir++)  /*Geçici blok sıfırla */{
		for (sutun = 0; sutun <= 3; sutun++){
			gecici_block[satir][sutun] = 0;
		}
	}
	sonraki_block = rand() % 7;
	for (i = 0; i <= 3; i++)    //Blok şekli oluştur
	{
		satir = (block[sonraki_block][i] / genislik) + 1;
		sutun = (block[sonraki_block][i] % genislik) - 3;
		gecici_block[satir][sutun] = 1;
	}
}
void oyun_sonu_kontrol(){
	int satir, sutun;
	int  deger = 0;
	bool deg = false;
	for (sutun = 0; sutun <= genislik - 1; sutun++) {
		for (satir = 0; satir <= yukseklik - 1; satir++)  {
			if (oyunAlaný[satir][sutun] == 1) 
				deger++;
			if (deger >= yukseklik)	{
					deg = true; 
					break; 
							}
		}
		deger = 0;
	}
	if (deg) {
		for (satir = 0; satir <= yukseklik - 1; satir++)  {
			for (sutun = 0; sutun <= genislik - 1; sutun++) {
				oyunAlaný[satir][sutun] = 0;
			}
		}
		skor = 0;
		rest(500);
	}
}

void block_seklini_belirle() {
	int satir,sutun,i;
	for (i = 0; i <= 3; i++) {    
		satir = (block[x][i] / genislik) - 1;
		sutun = (block[x][i] % genislik);
		if (satir >= 0)
			oyunAlaný[satir][sutun] = 0;
	}
}
