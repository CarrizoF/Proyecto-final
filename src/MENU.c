/*******************************
 * MENU.c
 *******************************/

#include "MENU.h"


uint8_t CardID[7];
uint32_t Tick;
uint32_t LocalSystick1=0;

SD_Card card = {"/","datos.txt",1};





int i=0;
char charestudio[2]={' ',' '};
char chardescanso[2]={' ',' '};
int estudio=20;
int estudioaux=20;
int descanso=5;
int descansoaux=5;

int ALERTA;


enum  {
	Bienvenido,
	Visor1,
	Visor2,
	Pomodoro,
	Pomodoro_OK,
	t_estudio,
	t_descanso,
	Tag_check,
	Activo,
	Descanso,
	Alerta,
	Datos,
	Fin_descanso,
	Estudio_OK,

}opciones;



void Menu (Tecla)
{
	switch ( opciones )
	{

	case Bienvenido:
		UB_LCD_2x16_Clear();
		UB_LCD_2x16_String(0,0,"Bienvenido!");
		UB_LCD_2x16_String(0,1,"Estas listo?");

		if (Tecla == 'C'){				// para ingresar al menu
			opciones = Visor1;
			break;}

		opciones = opciones - 20;			// -20 para ir a la opcion default
		break;



	case Visor1:
		UB_LCD_2x16_Clear();
		UB_LCD_2x16_String(0,0,">1-Pomodoro");
		UB_LCD_2x16_String(0,1," 2-Personalizado");


		if (Tecla == 'C'){
			opciones = Pomodoro;
			break;}

		if (Tecla == 'B'){
			opciones = Visor2;
			break;}

		opciones = opciones - 20;			// -20 para ir a la opcion default
		break;



	case Visor2:
		UB_LCD_2x16_Clear();
		UB_LCD_2x16_String(0,0," 1-Pomodoro");
		UB_LCD_2x16_String(0,1,">2-Personalizado");

		CE_mount_SD(card, 0);
		CE_write_SD(card, "datos.txt", "\n anda", 0);
		CE_write_SD(card, "datos.txt", "\n perfecto", 0);
		CE_unmount_SD(card, 1);

		if (Tecla == 'C'){
			opciones = t_estudio;				// configuracion t estudio
			UB_LCD_2x16_String(0,0,"Ingrese tiempo");
			UB_LCD_2x16_String(0,1,"de estudio:      ");
			break;}

		if (Tecla == 'B' || Tecla == 'A' ){
			opciones = Visor1;
			break;}


		opciones = opciones - 20;			// -20 para ir a la opcion default
		break;




	case Pomodoro:
		UB_LCD_2x16_Clear();
		UB_LCD_2x16_String(0,0," Programa 20-5");
		UB_LCD_2x16_String(0,1," Presione C");

		if (Tecla == 'C'){
			opciones = Pomodoro_OK;
			break;}

		if (Tecla == 'D'){
			opciones = Visor2;
			break;}

		opciones = opciones - 20;			// -20 para ir a la opcion default
		break;




	case t_estudio :

		if ( isdigit(Tecla) )     // si presiono un numero
		{
			charestudio[i]= Tecla;
			UB_LCD_2x16_String(11+i,1,&charestudio[i]);
			UB_LCD_2x16_String(12+i,1,"    ");
			i++;
		}


		if (Tecla == 'D'){
			i=0;
			opciones = Visor1;
			break;}


		if (Tecla == 'C'){
			UB_LCD_2x16_String(0,0,"Ingrese tiempo");
			UB_LCD_2x16_String(0,1,"de descanso:      ");
			opciones = t_descanso;
			i=0;

			estudio = atoi(charestudio);
			estudioaux = estudio;

			break;}


		opciones = opciones - 20;			// -20 para ir a la opcion default
		break;



	case t_descanso:

		if ( isdigit(Tecla) )     // si presiono un numero
		{
			chardescanso[i]= Tecla;
			UB_LCD_2x16_String(12+i,1,&chardescanso[i]);
			UB_LCD_2x16_String(13+i,1,"    ");
			i++;
		}

		if (Tecla == 'D'){
			i=0;
			opciones = Visor1;
			break;}


		if (Tecla == 'C'){
			opciones=Tag_check;
			i=0;
			descanso = atoi(chardescanso);

			break;}



		opciones = opciones - 20;			// -20 para ir a la opcion default
		break;



	case Tag_check:
		UB_LCD_2x16_Clear();
		UB_LCD_2x16_String(0,0,"Apoya el celular");
		UB_LCD_2x16_String(0,1,"en la base");

		while (!(TM_MFRC522_Check(CardID) == MI_OK))
		{

		}
		opciones=Activo;

		opciones = opciones - 20;			// -20 para ir a la opcion default
		break;


	case Activo:
		UB_LCD_2x16_Clear();
		UB_LCD_2x16_String(0,0,"Estudiando...");
		UB_LCD_2x16_String(0,1,"Queda   seg");
		estudioaux=estudio;

		while(TM_MFRC522_Check(CardID) == MI_OK && estudioaux>=0)
		{

			if( Tick )
			{
				Tick=0;

				if ( (Systick - LocalSystick1) > 400 ) // entra cada "" 1seg ""
				{
					LocalSystick1 = Systick;
					UB_LCD_2x16_String(6,1,charestudio);

					sscanf(charestudio, "%d", &estudioaux);
					estudioaux--;
					sprintf(charestudio, "%d", estudioaux);

					if(estudioaux<10)
						charestudio[1]= ' ';
				}
			}


		}

		if (!(TM_MFRC522_Check(CardID) == MI_OK) && estudio>0)
		{
			opciones=Alerta;
			break;
		}

		UB_LCD_2x16_Clear();
		UB_LCD_2x16_String(0,0,"Fin del tiempo");
		UB_LCD_2x16_String(0,1,"Presione C");		// para entrar en modo descanso


		opciones = Descanso;			// -20 para ir a la opcion default
		opciones = opciones - 20;
		break;





	case Alerta:
		UB_LCD_2x16_Clear();
		UB_LCD_2x16_String(0,0,"DEJALO AHI");
		UB_LCD_2x16_String(0,1,"BIGOTE");

		// ALERTA BTH DE USO DE CELULAR EN TIEMPO DE ESTUDIO
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // espero reg libre para enviar

		for (int x = 0; x < 4; x++)
		{
			while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
			USART_SendData(USART2, 'A');
		}


		while (!(TM_MFRC522_Check(CardID) == MI_OK))

		opciones=Activo;
		break;



	case Descanso:

		if(Tecla =='C')
		{
			UB_LCD_2x16_Clear();
			UB_LCD_2x16_String(0,0,"Descansando...");
			UB_LCD_2x16_String(0,1,"Queda   seg");
			descansoaux=descanso;

			while(descansoaux>=0)
			{
				if( Tick )
				{
					Tick=0;

					if ( (Systick - LocalSystick1) > 400 ) // entra cada "" 1seg ""
					{
						LocalSystick1 = Systick;
						UB_LCD_2x16_String(6,1,chardescanso);

						sscanf(chardescanso, "%d", &descansoaux);
						descansoaux--;
						sprintf(chardescanso, "%d", descansoaux);

						if(descansoaux<10)
							chardescanso[1]= ' ';
					}
				}

			}

			UB_LCD_2x16_Clear();
			UB_LCD_2x16_String(0,0,"Fin del descanso");
			UB_LCD_2x16_String(0,1,"Presione C");

			opciones=Fin_descanso;
			opciones=opciones-20;
			break;

		}

		break;


	case Fin_descanso:

		if(Tecla == 'C')
			opciones=Tag_check;

		opciones=opciones-20;
		break;







	default:
		Tecla = teclado();

		while(Tecla == 'X' && !(TM_MFRC522_Check(CardID) == MI_OK)) 	// si no se presiona una tecla o no se apoya el celular
			Tecla = teclado();

		if ((TM_MFRC522_Check(CardID) == MI_OK) && estudioaux>0)		// se apoya el celular sin configurar tiempos
		{
			opciones=Activo;
			break;
		}

		opciones= opciones + 20;	// +20 para volver al ultimo case
		break;
	}
}

void Menuinit()
{
	GPIO_SetBits( GPIOF, GPIO_Pin_7) ; // Backlight
	GPIO_SetBits( GPIOA, GPIO_Pin_12);//  naranja
	opciones=Bienvenido;
}

