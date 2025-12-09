#include "../../src/platform.h"

// 2025 - v01 - Converted to SDL2 via platform abstraction layer

// DECLARACOES INICIAIS //
int sair=0; void sair_callback() {sair=1;}; 
int timer=0; void tempo() {timer++;};
int Ctrl_FPS=60; float delay=0;

// INICIALIZACAO //
int main()
{
  platform_init();
  platform_install_timer();
  platform_install_keyboard();
  platform_install_mouse(); 
  platform_set_color_depth(32);
  platform_set_gfx_mode(PGFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  platform_install_int_ex(tempo, PLATFORM_BPS_TO_TIMER(60)); //60fps
  platform_set_window_title("SDL2 PALLETE GENERATOR");
  platform_set_close_button_callback( sair_callback );
  platform_install_sound(PDIGI_AUTODETECT, PMIDI_AUTODETECT, NULL);
  PlatformBitmap *buffer = platform_create_bitmap(640,480);
  PlatformBitmap *screen = platform_get_screen();
	
	// Declaracão de variáveis
  int x, y;
  int Pal0found, Pal1found, Pal2found, Pal3found, Pal4found, Pal5found, Pal6found, Pal7found, Pal8found;
  Pal0found = Pal1found = Pal2found = Pal3found = Pal4found = Pal5found = Pal6found = Pal7found = Pal8found = 1;
	int Palletefound=1;
	int ModoFullscreen=0;
	int ArrayPallete[32][4];
	int r=0, g=0, b=0, ValorDeCor=0;
	int CorNum=0;
	int podeatualizar=1;
	int AtualizaSlotPallete=0;
	int SlotNum=0;
	int ATUALIZA_S0=0; int ATUALIZA_S1=0; int ATUALIZA_S2=0; int ATUALIZA_S3=0;
	int ATUALIZA_S4=0; int ATUALIZA_S5=0; int ATUALIZA_S6=0; int ATUALIZA_S7=0;
	int ATUALIZA_S8=0; int GERAR_NOVA_PALETA=0;
	int Slot0OK=0; int Slot1OK=0; int Slot2OK=0; int Slot3OK=0;
	int Slot4OK=0; int Slot5OK=0; int Slot6OK=0; int Slot7OK=0; 
	int Slot8OK=0;
	
	for(y = 0; y < 4; y++) {
   	for(x = 0; x < 32; x++) {
			ArrayPallete[x][y]=0; //zera o array
		};
	};
	
	// Declaração de Bitmaps
	PlatformBitmap *bmp;
	PlatformBitmap *SlotPallete = platform_create_bitmap(32,10);
	SlotPallete = platform_load_bitmap("data/pallete.pcx", NULL); if (!SlotPallete) { Palletefound=0; };
	if(Palletefound==0){
		bmp = platform_create_sub_bitmap(screen, 0, 0, 32, 10); 
		platform_clear_to_color(bmp, platform_makecol(255, 000, 255)); 
		platform_save_bitmap("data/pallete.pcx", bmp, NULL);
		SlotPallete = platform_load_bitmap("data/pallete.pcx", NULL); 
	};
	PlatformBitmap *SlotPalleteDisplay = platform_create_bitmap(256,80);
	PlatformBitmap *EditorBackground = platform_load_bitmap("data/system/EditorBackground.pcx", NULL);
	PlatformBitmap *SlotVazio = platform_load_bitmap("data/system/SlotVazio.pcx", NULL);
	PlatformBitmap *StatusOK  = platform_load_bitmap("data/system/StatusOK.pcx", NULL);
	PlatformBitmap *StripPal0 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal0, platform_makecol(255, 000, 255)); 
	PlatformBitmap *StripPal1 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal1, platform_makecol(255, 000, 255));
	PlatformBitmap *StripPal2 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal2, platform_makecol(255, 000, 255));
	PlatformBitmap *StripPal3 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal3, platform_makecol(255, 000, 255));
	PlatformBitmap *StripPal4 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal4, platform_makecol(255, 000, 255));
	PlatformBitmap *StripPal5 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal5, platform_makecol(255, 000, 255));
	PlatformBitmap *StripPal6 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal6, platform_makecol(255, 000, 255));
	PlatformBitmap *StripPal7 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal7, platform_makecol(255, 000, 255));
	PlatformBitmap *StripPal8 = platform_create_bitmap(32,1); platform_clear_to_color(StripPal8, platform_makecol(255, 000, 255));
	PlatformBitmap *Slot0 = platform_load_bitmap("data/pal0.pcx", NULL); if (!Slot0) { Pal0found=0; };
	PlatformBitmap *Slot1 = platform_load_bitmap("data/pal1.pcx", NULL); if (!Slot1) { Pal1found=0; };
	PlatformBitmap *Slot2 = platform_load_bitmap("data/pal2.pcx", NULL); if (!Slot2) { Pal2found=0; };
	PlatformBitmap *Slot3 = platform_load_bitmap("data/pal3.pcx", NULL); if (!Slot3) { Pal3found=0; };
	PlatformBitmap *Slot4 = platform_load_bitmap("data/pal4.pcx", NULL); if (!Slot4) { Pal4found=0; };
	PlatformBitmap *Slot5 = platform_load_bitmap("data/pal5.pcx", NULL); if (!Slot5) { Pal5found=0; };
	PlatformBitmap *Slot6 = platform_load_bitmap("data/pal6.pcx", NULL); if (!Slot6) { Pal6found=0; };
	PlatformBitmap *Slot7 = platform_load_bitmap("data/pal7.pcx", NULL); if (!Slot7) { Pal7found=0; };
	PlatformBitmap *Slot8 = platform_load_bitmap("data/pal8.pcx", NULL); if (!Slot8) { Pal8found=0; };
  
	// Get default font
	PlatformFont *font = platform_get_default_font();
	
	// Get key state array
	volatile char *key = platform_get_key_state();
  
  // LOOP DE JOGO // 
  while (sair==0)
  { 
	
	delay=timer; platform_clear_to_color(buffer, platform_makecol(100,149,237)); 
	
	// Update key state
	key = platform_get_key_state();
	if (key[PKEY_ESC]) {sair=1;}; 
	
	/* < INICIO > */
	
	if (ModoFullscreen==0 && key[PKEY_ALT] && key[PKEY_ENTER]) {ModoFullscreen=1; platform_set_gfx_mode(PGFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0);};
	if (ModoFullscreen==1 && key[PKEY_ALT] && key[PKEY_ENTER]) {ModoFullscreen=0; platform_set_gfx_mode(PGFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);};
	
	if(key[PKEY_F1]){
	ATUALIZA_S0=1;
	ATUALIZA_S1=1;
	ATUALIZA_S2=1;
	ATUALIZA_S3=1;
	ATUALIZA_S4=1;
	ATUALIZA_S5=1;
	ATUALIZA_S6=1;
	ATUALIZA_S7=1;
	ATUALIZA_S8=1;
	GERAR_NOVA_PALETA=1;
	};
	
	if(ATUALIZA_S0==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot0->h; y++) { for(x = 0; x < Slot0->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot0, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot0, x, y); 
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot0->h; y++) { for(x = 0; x < Slot0->w; x++) { if(platform_getpixel(Slot0, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot0, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal0, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S0=0; };
	
	if(ATUALIZA_S1==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot1->h; y++) { for(x = 0; x < Slot1->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot1, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot1, x, y);
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot1->h; y++) { for(x = 0; x < Slot1->w; x++) { if(platform_getpixel(Slot1, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot1, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal1, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S1=0; };
	
	if(ATUALIZA_S2==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot2->h; y++) { for(x = 0; x < Slot2->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot2, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot2, x, y);
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot2->h; y++) { for(x = 0; x < Slot2->w; x++) { if(platform_getpixel(Slot2, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot2, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal2, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S2=0; };
	
	if(ATUALIZA_S3==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot3->h; y++) { for(x = 0; x < Slot3->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot3, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot3, x, y);
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot3->h; y++) { for(x = 0; x < Slot3->w; x++) { if(platform_getpixel(Slot3, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot3, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal3, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S3=0; };
	
	if(ATUALIZA_S4==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot4->h; y++) { for(x = 0; x < Slot4->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot4, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot4, x, y);
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot4->h; y++) { for(x = 0; x < Slot4->w; x++) { if(platform_getpixel(Slot4, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot4, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal4, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S4=0; };
	
	if(ATUALIZA_S5==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot5->h; y++) { for(x = 0; x < Slot5->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot5, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot5, x, y);
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot5->h; y++) { for(x = 0; x < Slot5->w; x++) { if(platform_getpixel(Slot5, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot5, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal5, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S5=0; };
	
	if(ATUALIZA_S6==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot6->h; y++) { for(x = 0; x < Slot6->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot6, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot6, x, y);
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot6->h; y++) { for(x = 0; x < Slot6->w; x++) { if(platform_getpixel(Slot6, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot6, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal6, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S6=0; };
	
	if(ATUALIZA_S7==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot7->h; y++) { for(x = 0; x < Slot7->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot7, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot7, x, y);
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot7->h; y++) { for(x = 0; x < Slot7->w; x++) { if(platform_getpixel(Slot7, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot7, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal7, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S7=0; };
	
	if(ATUALIZA_S8==1){ 
		for(int i=1; i<=32; i++) { podeatualizar=1;
		for(y = 0; y < Slot8->h; y++) { for(x = 0; x < Slot8->w; x++) { if(podeatualizar==1) {
		if(platform_getpixel(Slot8, x, y) != platform_makecol( 255,000,255)){ ValorDeCor = platform_getpixel(Slot8, x, y);
		r = platform_getr(ValorDeCor); g = platform_getg(ValorDeCor); b = platform_getb(ValorDeCor);
		ArrayPallete[CorNum][1]=r; ArrayPallete[CorNum][2]=g; ArrayPallete[CorNum][3]=b; CorNum++; podeatualizar=0;};};};};
		for(y = 0; y < Slot8->h; y++) { for(x = 0; x < Slot8->w; x++) { if(platform_getpixel(Slot8, x, y) == platform_makecol( r,g,b)){
		platform_putpixel(Slot8, x, y, platform_makecol(255,000,255));};};};
		if(CorNum>33){CorNum=33;}; if(i==32){AtualizaSlotPallete=1;};};};
	if(AtualizaSlotPallete==1){ for(int i=0; i<=CorNum-1; i++){
		platform_putpixel(StripPal8, i, 0, platform_makecol(ArrayPallete[i][1],ArrayPallete[i][2],ArrayPallete[i][3]));	}; AtualizaSlotPallete=0; CorNum=0; ATUALIZA_S8=0; };
	
	if(GERAR_NOVA_PALETA==1){
		platform_blit(StripPal0, SlotPallete, 0, 0, 0, 0, 32, 1);
		platform_blit(StripPal1, SlotPallete, 0, 0, 0, 1, 32, 1);
		platform_blit(StripPal2, SlotPallete, 0, 0, 0, 2, 32, 1);
		platform_blit(StripPal3, SlotPallete, 0, 0, 0, 3, 32, 1);
		platform_blit(StripPal4, SlotPallete, 0, 0, 0, 4, 32, 1);
		platform_blit(StripPal5, SlotPallete, 0, 0, 0, 5, 32, 1);
		platform_blit(StripPal6, SlotPallete, 0, 0, 0, 6, 32, 1);
		platform_blit(StripPal7, SlotPallete, 0, 0, 0, 7, 32, 1);
		platform_blit(StripPal8, SlotPallete, 0, 0, 0, 8, 32, 1);
		platform_save_bitmap("data/pallete.pcx", SlotPallete, NULL);
		if(Pal0found==1){ Slot0OK=1; };
		if(Pal1found==1){ Slot1OK=1; };
		if(Pal2found==1){ Slot2OK=1; };
		if(Pal3found==1){ Slot3OK=1; };
		if(Pal4found==1){ Slot4OK=1; };
		if(Pal5found==1){ Slot5OK=1; };
		if(Pal6found==1){ Slot6OK=1; };
		if(Pal7found==1){ Slot7OK=1; };
		if(Pal8found==1){ Slot8OK=1; };
	GERAR_NOVA_PALETA=0;
	};
	
	platform_draw_sprite(buffer,EditorBackground,0,0);
  
	platform_textprintf_centre_ex(buffer, font, 320,  20, platform_makecol(255,255,255), -1, "HAMOOPI - PALLETE GENERATOR");
	platform_textprintf_centre_ex(buffer, font, 320,  35, platform_makecol(255,255,255), -1, "Aperte F1 para criar uma nova paleta");
	platform_textprintf_centre_ex(buffer, font, 320,  45, platform_makecol(255,255,255), -1, "Aperte ESC para sair");
	
	//desenha SlotPallete
	platform_stretch_blit(SlotPallete, SlotPalleteDisplay, 
	0, 0, SlotPallete->w, SlotPallete->h, 
	0, 0, SlotPalleteDisplay->w, SlotPalleteDisplay->h);
	platform_draw_sprite(buffer, SlotPalleteDisplay, 252, 91);
	
	//desenha slots
	if (Pal0found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*0+0, 76+128*0+0); };
	if (Pal1found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*0+0, 76+128*1+2); };
	if (Pal2found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*1+2, 76+128*1+2); };
	if (Pal3found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*2+4, 76+128*1+2); };
	if (Pal4found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*3+6, 76+128*1+2); };
	if (Pal5found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*0+0, 76+128*2+4); };
	if (Pal6found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*1+2, 76+128*2+4); };
	if (Pal7found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*2+4, 76+128*2+4); };
	if (Pal8found==0) { platform_draw_sprite(buffer, SlotVazio, 64+128*3+6, 76+128*2+4); };
	
	if (Pal0found==1) { platform_draw_sprite(buffer, Slot0, 64+128*0+0, 76+128*0+0); };
	if (Pal1found==1) { platform_draw_sprite(buffer, Slot1, 64+128*0+0, 76+128*1+2); };
	if (Pal2found==1) { platform_draw_sprite(buffer, Slot2, 64+128*1+2, 76+128*1+2); };
	if (Pal3found==1) { platform_draw_sprite(buffer, Slot3, 64+128*2+4, 76+128*1+2); };
	if (Pal4found==1) { platform_draw_sprite(buffer, Slot4, 64+128*3+6, 76+128*1+2); };
	if (Pal5found==1) { platform_draw_sprite(buffer, Slot5, 64+128*0+0, 76+128*2+4); };
	if (Pal6found==1) { platform_draw_sprite(buffer, Slot6, 64+128*1+2, 76+128*2+4); };
	if (Pal7found==1) { platform_draw_sprite(buffer, Slot7, 64+128*2+4, 76+128*2+4); };
	if (Pal8found==1) { platform_draw_sprite(buffer, Slot8, 64+128*3+6, 76+128*2+4); };
	
	if (Slot0OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*0+0, 32+76+128*0+0); };
	if (Slot1OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*0+0, 32+76+128*1+2); };
	if (Slot2OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*1+2, 32+76+128*1+2); };
	if (Slot3OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*2+4, 32+76+128*1+2); };
	if (Slot4OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*3+6, 32+76+128*1+2); };
	if (Slot5OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*0+0, 32+76+128*2+4); };
	if (Slot6OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*1+2, 32+76+128*2+4); };
	if (Slot7OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*2+4, 32+76+128*2+4); };
	if (Slot8OK==1) { platform_draw_sprite(buffer, StatusOK, 32+64+128*3+6, 32+76+128*2+4); };
	
	//textos
	
	platform_textprintf_right_ex(buffer, font, 122+128*0+0+64+1, 76+128*0+0+116+1-110, platform_makecol(000,000,000), -1, "LP");
	platform_textprintf_right_ex(buffer, font, 122+128*0+0+64+0, 76+128*0+0+116+0-110, platform_makecol(255,255,255), -1, "LP");
	platform_textprintf_right_ex(buffer, font, 122+128*0+0+64+1, 212+1, platform_makecol(000,000,000), -1, "MP");
	platform_textprintf_right_ex(buffer, font, 122+128*0+0+64+0, 212+0, platform_makecol(255,255,255), -1, "MP");
	platform_textprintf_right_ex(buffer, font, 122+128*1+0+66+1, 212+1, platform_makecol(000,000,000), -1, "HP");
	platform_textprintf_right_ex(buffer, font, 122+128*1+0+66+0, 212+0, platform_makecol(255,255,255), -1, "HP");
	platform_textprintf_right_ex(buffer, font, 122+128*2+0+68+1, 212+1, platform_makecol(000,000,000), -1, "LK");
	platform_textprintf_right_ex(buffer, font, 122+128*2+0+68+0, 212+0, platform_makecol(255,255,255), -1, "LK");
	platform_textprintf_right_ex(buffer, font, 122+128*3+0+70+1, 212+1, platform_makecol(000,000,000), -1, "MK");
	platform_textprintf_right_ex(buffer, font, 122+128*3+0+70+0, 212+0, platform_makecol(255,255,255), -1, "MK");
	
	platform_textprintf_right_ex(buffer, font, 122+128*0+0+64+1, 130+212+1, platform_makecol(000,000,000), -1, "HK");
	platform_textprintf_right_ex(buffer, font, 122+128*0+0+64+0, 130+212+0, platform_makecol(255,255,255), -1, "HK");
	platform_textprintf_right_ex(buffer, font, 122+128*1+0+66+1, 130+212+1, platform_makecol(000,000,000), -1, "SELECT");
	platform_textprintf_right_ex(buffer, font, 122+128*1+0+66+0, 130+212+0, platform_makecol(255,255,255), -1, "SELECT");
	platform_textprintf_right_ex(buffer, font, 122+128*2+0+68+1, 130+212+1, platform_makecol(000,000,000), -1, "START");
	platform_textprintf_right_ex(buffer, font, 122+128*2+0+68+0, 130+212+0, platform_makecol(255,255,255), -1, "START");
	platform_textprintf_right_ex(buffer, font, 122+128*3+0+70+1, 130+212+1, platform_makecol(000,000,000), -1, "HOLD");
	platform_textprintf_right_ex(buffer, font, 122+128*3+0+70+0, 130+212+0, platform_makecol(255,255,255), -1, "HOLD");
	
	platform_textprintf_centre_ex(buffer, font, 64+128*0+0+64+1, 76+128*0+0+116+1, platform_makecol(000,000,000), -1, "data/pal0.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*0+0+64+0, 76+128*0+0+116+0, platform_makecol(255,255,255), -1, "data/pal0.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*0+0+64+1, 76+128*1+0+118+1, platform_makecol(000,000,000), -1, "data/pal1.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*0+0+64+0, 76+128*1+0+118+0, platform_makecol(255,255,255), -1, "data/pal1.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*1+0+64+1, 76+128*1+0+118+1, platform_makecol(000,000,000), -1, "data/pal2.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*1+0+64+0, 76+128*1+0+118+0, platform_makecol(255,255,255), -1, "data/pal2.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*2+0+64+1, 76+128*1+0+118+1, platform_makecol(000,000,000), -1, "data/pal3.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*2+0+64+0, 76+128*1+0+118+0, platform_makecol(255,255,255), -1, "data/pal3.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*3+0+64+1, 76+128*1+0+118+1, platform_makecol(000,000,000), -1, "data/pal4.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*3+0+64+0, 76+128*1+0+118+0, platform_makecol(255,255,255), -1, "data/pal4.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*0+0+64+1, 76+128*2+0+120+1, platform_makecol(000,000,000), -1, "data/pal5.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*0+0+64+0, 76+128*2+0+120+0, platform_makecol(255,255,255), -1, "data/pal5.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*1+0+64+1, 76+128*2+0+120+1, platform_makecol(000,000,000), -1, "data/pal6.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*1+0+64+0, 76+128*2+0+120+0, platform_makecol(255,255,255), -1, "data/pal6.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*2+0+64+1, 76+128*2+0+120+1, platform_makecol(000,000,000), -1, "data/pal7.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*2+0+64+0, 76+128*2+0+120+0, platform_makecol(255,255,255), -1, "data/pal7.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*3+0+64+1, 76+128*2+0+120+1, platform_makecol(000,000,000), -1, "data/pal8.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*3+0+64+0, 76+128*2+0+120+0, platform_makecol(255,255,255), -1, "data/pal8.pcx");
	
	platform_textprintf_centre_ex(buffer, font, 64+128*2+0+64+1, 76+128*0+0+102+1, platform_makecol(000,000,000), -1, "data/pallete.pcx");
	platform_textprintf_centre_ex(buffer, font, 64+128*2+0+64+0, 76+128*0+0+102+0, platform_makecol(255,255,255), -1, "data/pallete.pcx");
	
	//DEBUG
	platform_draw_sprite(buffer, StripPal0, 80, 30+3);
	platform_draw_sprite(buffer, StripPal1, 80, 32+3);
	platform_draw_sprite(buffer, StripPal2, 80, 34+3);
	platform_draw_sprite(buffer, StripPal3, 80, 36+3);
	platform_draw_sprite(buffer, StripPal4, 80, 38+3);
	platform_draw_sprite(buffer, StripPal5, 80, 40+3);
	platform_draw_sprite(buffer, StripPal6, 80, 42+3);
	platform_draw_sprite(buffer, StripPal7, 80, 44+3);
	platform_draw_sprite(buffer, StripPal8, 80, 46+3);
	
	platform_draw_sprite(screen, buffer, 0, 0);
		
  // FINALIZACOES //
	while(timer==delay){};	
	platform_clear(buffer);
  }; 
  platform_destroy_bitmap(buffer);
  return 0;
};


//Pallete Editor by Daniel Moura - danielmouradesigner@gmail.com - 16/03/2019
//Converted to SDL2 platform abstraction layer - 2025

