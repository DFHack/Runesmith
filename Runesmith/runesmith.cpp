#include "runesmith.h"
#include "rsException.h"

Runesmith::Runesmith(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);	

	try
    {
		DF = new DFHack::API("Memory.xml");
        DF->Attach();
    }
	catch (std::exception& e)
    {
        throw;
    }

	Creatures = DF->getCreatures();
    Materials = DF->getMaterials();
	Tran = DF->getTranslation();
	Materials->ReadAllMaterials();

	if(!Creatures->Start(numCreatures))
		throw RSException();    

    if(!numCreatures)
		throw RSException();	

	if(!Tran->Start())
		throw RSException();

	if(!(dTM = new dwarfTableModel(*DF, this)))
		throw RSException();

	dTM->update(numCreatures);
	ui.dwarvesTV->setModel(dTM);	
}

Runesmith::~Runesmith()
{
	if(dTM)
		delete dTM;
	Creatures->Finish();
	Tran->Finish();
    DF->Detach();	
}
