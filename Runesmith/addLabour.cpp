#include "addLabour.h"
#include "RSCreature.h"
#include "DFInterface.h"

addLabour::addLabour(QWidget *parent,
				   Qt::WFlags flags, 
				   RSCreature* creature,
				   DFInterface *nDFI) 
				   : index(-1), DFI(nDFI)
{
	labDia.setupUi(this);
	unsigned int indexCount = 0;

	if(DFI && creature)
	{
		DFHack::t_creature rawCreature = creature->getRawCreature();
		std::map<uint32_t, std::string> const& labs = DFI->getAllLabours();

		for(unsigned int i=0; i<labs.size(); i++)
		{			
			if(!rawCreature.labors[i])
			{
				labDia.labourCmb->addItem(labs.find(i)->second.c_str());
				IDs[indexCount] = i;
				indexCount++;
			}
		}
	}

	QApplication::connect(labDia.addButton, SIGNAL(clicked()), 
		this, SLOT(storeChoice()));
}

addLabour::~addLabour(void)
{
}

int addLabour::getIndex()
{
	return index;
}

void addLabour::storeChoice()
{
	index = IDs[labDia.labourCmb->currentIndex()];
	this->close();	
}
