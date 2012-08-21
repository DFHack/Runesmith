#include "addTrait.h"
#include "traitsTableModel.h"

addTrait::addTrait(QWidget *parent,
				   Qt::WFlags flags, 
				   RSCreature* creature,
				   DFInterface *nDFI) 
				   : index1(-1), index2(-1), DFI(nDFI)
{
	atD.setupUi(this);
	int first = -1;
	unsigned int indexCount = 0;

	if(DFI && creature)
	{
		std::vector< std::vector<std::string> > const& traits =	
			DFI->getAllTraits();

		for(unsigned int i=0; i<NUM_CREATURE_TRAITS; i++)
		{			
			if(DFI->translateTrait(i, 
				creature->getRawCreature().defaultSoul.traits[i]) == "")
			{
				if(first == -1)
					first = i;
				atD.categoryCB->addItem(traits[i][6].c_str());
				IDs[indexCount] = i;
				indexCount++;
			}
		}

		if(first > -1)
		{
			for(int i=0; i<6; i++)
			{
				atD.levelCB->addItem(traits[first][i].c_str());
			}
		}
	}

	QApplication::connect(atD.categoryCB, SIGNAL(currentIndexChanged(int)),
		this, SLOT(populateLevel(int)));

	QApplication::connect(atD.addButton, SIGNAL(clicked()), 
		this, SLOT(addAction()));
}

addTrait::~addTrait(void)
{
}

void addTrait::populateLevel(int index)
{
	if(DFI)
	{
		std::vector< std::vector<std::string> > const& traits = 
			DFI->getAllTraits();

		atD.levelCB->clear();

		for(int i=0; i<6; i++)
		{
			atD.levelCB->addItem(traits[IDs[index]][i].c_str());
		}
	}
}

int addTrait::getIndex1()
{
	return index1;
}

int addTrait::getIndex2()
{
	return index2;
}

void addTrait::addAction()
{
	if(DFI)
	{
		index1 = IDs[atD.categoryCB->currentIndex()];
		index2 = atD.levelCB->currentIndex();
		this->close();
	}
}
