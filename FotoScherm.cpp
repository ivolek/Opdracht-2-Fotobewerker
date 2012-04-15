/*
 * FotoScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: Ivo Lek
 */

#include "FotoScherm.h"
#include <conprint.h>
FotoScherm::FotoScherm()
{
	//	//het optiescherm
	////	this->optieScherm = new OptieScherm( this );
	//
	//
	//	//bepaal grootte van het scherm
	//
	//	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	//	Font* font = new MAUI::Font(RES_FONT);
	//	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );
	//
	//	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	////Label* labl = new Label(0,0,0,0, NULL);
	//	Label* label1;
	////label1->setBackgroundColor(0xffffff);
	//
	//printf("1234");
	//	//maak een plaatje (laden uit de resource file res.lst) en voeg label als parent toe
	////	Image* image = new Image(50, 50, 60, 80, NULL,  false, false,RES_IMAGE);
	//	//maak tekst bij het plaatje met een label
	//
	//	//stel dit scherm in als het main scherm, met achtergrondlabel als de basis widget
	//	this->setMain(achtergrondLabel );
//
//	Font* font = new Font(RES_FONT);
//	WidgetSkin* skin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false);
//
//	Image* image = new Image(50, 50, 60, 80, NULL,  false, false,RES_IMAGE);
//	//	image.setImage(IMAGE1_SMALL);
//
//
//
//
//	Label* label = new Label(0,0,0,0, NULL);
//	label->setBackgroundColor(0x00ff00);
//
//	//printf("1234");
//	//Label* imageTekst = new Label(50, 50, 100, 70, label, "Mijn labeltje", 0, font);
//	//	imageTekst->setSkin(skin);
//	//	image->setSkin(image);
//	//this->setMain(label);
//	image->setSkin(skin);
//	image->setDrawBackground(true);
//	this->setMain(image);



	//het optiescherm
	this->optieScherm = new OptieScherm( this );

	//bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	int screenWidth = EXTENT_X( screenSize );
	int screenHeight = EXTENT_Y( screenSize );

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	Label *achtergrondLabel = new Label(0,0,0,0,NULL);
	achtergrondLabel->setBackgroundColor(0xffffff);

	// stel width en height in van plaatje
	imageTekst = new Label( screenWidth/2 - 40, 250, 80, 30, achtergrondLabel, "", 0, font);
	imageTekst->setSkin(skin);
	imageTekst->setPaddingLeft(5);
	imageTekst->setPaddingTop(5);
	//maak een plaatje (laden uit de resource file res.lst) en voeg label als parent toe
	image = new Image(screenWidth/2-60,screenHeight/2-60, 120, 160, achtergrondLabel, false, false, RES_IMAGE);

	//dit scherm als standaard, met achtergrondlabel als basis widget (wisselt met OptieScherm)
	this->setMain(achtergrondLabel);

}


FotoScherm::~FotoScherm()
{

}


//show() override de show() van de super klasse (Screen), omdat we bij showen eerst opties willen ophalen
void FotoScherm::show()
{
	//roep de show() van de superklasse (Screen) aan
	this->Screen::show();

	//haal informatie achtergrondkleur op van optiescherm
	this->achtergrondLabel->setBackgroundColor( this->optieScherm->getAchtergrondOptie() );
	//
	//	//haal informatie imagetekst op van optiescherm
	this->imageTekst->setCaption( this->optieScherm->getImagetekst() );

	//haal informatie over afmetingen afbeeldingen
	this->image->setWidth(this->optieScherm->getImageSize());
	this->image->setHeight(this->optieScherm->getImageSize());
}



void FotoScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//bij indrukken van de MAK_FIRE toets, laat optiescherm zien
	if( keyCode == MAK_FIRE)
	{
			this->optieScherm->show();
	}

}

void FotoScherm::pointerPressEvent(MAPoint2d point)
{
	//bij touch, laat optiescherm zien
//	Point point;
//	point.x = p.x;
//	point.y = p.y;
//
//	if( this->imageText->contains( point) )
//	{
//		this->imageText->setSelected(true);
//	}
//	else
//	{
//		this->imageText->setSelected(false);
//	}
	optieScherm->show();
}


