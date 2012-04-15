///*
// * OptieScherm.cpp
// *
// *  Created on: 3 mrt. 2012
// *      Author: Ivo Lek
// */
//
#include "OptieScherm.h"


bool muisoplabel;

OptieScherm::OptieScherm( Screen* parent )
{
	//sla parent scherm op (FotoScherm) om de show() te kunnen aanroepen, zodat dit optiescherm weer gesloten wordt
	this->parent = parent;

	//	//bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	int screenWidth = EXTENT_X( screenSize );
	int screenHeight = EXTENT_Y( screenSize );

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	Label* label = new Label(0,0,0,0,NULL);

	//	//stel achtergrondkleur in
	label->setBackgroundColor(0xffffff);


	//	//maak rode knop
	this->roodLabel = new Label( screenWidth/2-50, 155, 80, 30, label, "Rood", 0, font );
	roodLabel->setSkin( skin );
	this->kleurLabels.add( roodLabel );	//voeg toe aan vector
	//
	//	//maak groene knop
	this->groenLabel = new Label( screenWidth/2-50, 155, 80, 30, label, "Groen", 0, font );
	groenLabel->setSkin( skin );
	this->kleurLabels.add( groenLabel );	//voeg toe aan vector
	//	//maak blauwe knop
	this->blauwLabel = new Label( screenWidth/2-50, 155, 80, 30, label, "Blauw", 0, font );
	blauwLabel->setSkin( skin );
	this->kleurLabels.add( blauwLabel );	//voeg toe aan vector

	// knop met toepassen
	this->toepassenLabel = new Label( screenWidth/2-50, 155, 80, 30, label, "Toepassen", 0, font );
	toepassenLabel->setSkin( skin );

	//stel naam plaatje in m.b.v. editbox
	this->imageTekst = new EditBox( 50, 50, 150, 30, label, "naam plaatje", 0x555500, font, true, false, 20, EditBox::IM_STANDARD );
	this->imageTekst->setSkin(skin);
	imageTekst->setPaddingLeft(5);
	imageTekst->setPaddingTop(5);

	//stel grootte plaatje in m.b.v. editbox
	this->imageSize = new EditBox( 50, 80, 40, 30, label, "grootte plaatje", 0x555500, font, true, false, 3, EditBox::IM_QWERTY);
	this->imageSize->setSkin(skin);
	imageSize->setPaddingLeft(5);
	imageSize->setPaddingTop(5);


	this->setMain( label );
}

OptieScherm::~OptieScherm()
{
	//verwijder objecten van deze klasse
}


//geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	//return achtergrond kleur
	return this->achtergrondKleur;
}


//geef ingestelde imagetekst van de editbox terug
const BasicString<char> OptieScherm::getImagetekst()
{
	//verander editBox naar jouw editboxs
	return this->imageTekst->getCaption(); //caption is de text in een editbox
}
//
//
//
void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//laat bij MAK_FIRE knop indrukken de parent (FotoScherm dus) weer zien
	if (keyCode == MAK_FIRE)
	{
		parent->show();
	}
	for( int i= 0; i<kleurLabels.size(); i++ )
	{
		//Bij drukken op knop, verander selectie
		//0 = rood
		//1 = groen
		//2 = blauw
		if (keyCode == MAK_DOWN)
		{
			if (kleurLabels[0]->isSelected())
			{
				achtergrondKleur = 0x00ff00;
				kleurLabels[0]->setSelected(false);
				kleurLabels[1]->setSelected(true);
				break;
			}
			else if (kleurLabels[1]->isSelected())
			{
				achtergrondKleur= 0x0000ff;
				kleurLabels[1]->setSelected(false);
				kleurLabels[2]->setSelected(true);
				break;
			}
			else if (kleurLabels[2]->isSelected())
			{
				achtergrondKleur= 0xff0000;
				kleurLabels[2]->setSelected(false);
				kleurLabels[0]->setSelected(true);
				break;
			}
		}

		if (keyCode == MAK_UP)
		{
			if (kleurLabels[0]->isSelected())
			{
				achtergrondKleur= 0x00ff00;
				kleurLabels[0]->setSelected(false);
				kleurLabels[2]->setSelected(true);
				break;
			}
			else if (kleurLabels[2]->isSelected())
			{
				achtergrondKleur = 0x00ff00;
				kleurLabels[2]->setSelected(false);
				kleurLabels[1]->setSelected(true);
				break;
			}
			else if (kleurLabels[1]->isSelected())
			{
				achtergrondKleur = 0xff0000;
				kleurLabels[1]->setSelected(false);
				kleurLabels[0]->setSelected(true);
				break;
			}
		}
	}
}
void OptieScherm::pointerPressEvent(MAPoint2d point)
{
	//	doorloop alle kleurlabels om selectie in te stellen
	for( int i= 0; i<kleurLabels.size(); i++ )
	{
		//kijk of label in het touch-punt valt
		for( int i= 0; i<kleurLabels.size(); i++ )
		{
			if (kleurLabels[i]->contains( point.x, point.y))
			{
				muisoplabel = true;
			}
			else if(!muisoplabel)
			{
				muisoplabel = false;
			}
		}

		if (muisoplabel)
		{
			muisoplabel = false;
			for( int i= 0; i<kleurLabels.size(); i++ )
			{
				if ( kleurLabels[i]->contains( point.x, point.y) )
				{
					kleurLabels[i]->setSelected(true);
					if (i == 0 ) // rood
					{
						achtergrondKleur = 0xff0000;
					}
					else if (i == 1) // groen
					{
						achtergrondKleur = 0x00ff00;
					}
					else if (i == 2 ) // blauw
					{
						achtergrondKleur= 0x0000ff;
					}
				}
				else
				{
					kleurLabels[i]->setSelected(false);
				}
			}
		}

		if ( imageTekst->contains(point.x, point.y) )
		{
			imageTekst->setSelected(true);
		}
		else
		{
			imageTekst->setSelected(false);
		}

		if (imageSize->contains(point.x, point.y))
		{
			imageSize->setSelected(true);
		}
		else
		{
			imageSize->setSelected(false);
		}

		if (imageSize->contains(point.x, point.y))
		{
			imageSize->setSelected(true);
		}
		else
		{
			imageSize->setSelected(false);
		}


		if ( toepassenLabel->contains(point.x, point.y ) )
		{
			parent->show();
		}
	}
}

//
//	//behandel de editbox bij selecteren (touch), verander de editBox naar je eigen editbox(en)
//	}
//}
int OptieScherm::getImageSize()
{

	grootte = atoi( this->imageSize->getCaption().c_str() );
	return grootte; //caption is de text in een editbox
}
