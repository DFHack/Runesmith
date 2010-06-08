#include "DFInterface.h"
#include "rsException.h"

DFInterface::DFInterface(void)
{
	try
	{
		DFMgr = new DFHack::ContextManager("Memory.xml");
		attach();   
	}
	catch (std::exception& e)
	{
		throw;
	}	
}

DFInterface::~DFInterface(void)
{
}

bool DFInterface::isContextValid()
{
	DFHack::BadContexts inval;
	DFMgr->Refresh(&inval);
	return !inval.Contains(DF);
}

bool DFInterface::attach()
{
	if(!DF)
	{
		try
		{
			DF = DFMgr->getSingleContext(); 
		}
		catch (std::exception& e)
		{
			throw;
		}
	}

	if(DF)
	{
		if(isContextValid())
		{

			try
			{
				DF->Attach();
			}
			catch (std::exception& e)
			{
				throw;
			}	

			Creatures = DF->getCreatures();
			Materials = DF->getMaterials();
			Tran = DF->getTranslation();
			suspend();	
			//process
			resume();
		}
	}	
}

void DFInterface::detatch()
{
	if(DF)
	{
		if(isContextValid())
		{
			if(DF->isAttached())
			{				
				suspend();
				DF->Detach();
				numCreatures = 0;
			}
		}
	}
}

void DFInterface::update()
{
	if(DF)
	{
		if(isContextValid())
		{
			if(DF->isAttached())
			{
				suspend();
				//process
				resume();
				return;
			}
		}
	}
}

std::vector<DFHack::t_creature>& DFInterface::getDwarves()
{
	return dwarves;
}

std::vector<DFHack::t_creature>& DFInterface::getCreatures()
{
	return creatures;
}

DFHack::t_creature& DFInterface::getDwarf(int dwarf)
{
	return dwarves[dwarf];
}

DFHack::t_creature& DFInterface::getCreature(int creature)
{
	return creatures[creature];
}

void DFInterface::resume()
{
	if(Creatures)
		Creatures->Finish();

	DF->Resume();
}

void DFInterface::suspend()
{
	if(Tran)
		Tran->Finish();

	DF->Suspend();	
	Materials->ReadAllMaterials();

	if(!Creatures->Start(numCreatures))
		throw RSException();    

	if(!numCreatures)
		throw RSException();

	if(!Tran->Start())
		throw RSException();
}

void DFInterface::process()
{
	//if(attached)
	//{
		creatures.clear();
		dwarves.clear();

		for(int i=0; i<numCreatures; i++)
		{
			DFHack::t_creature temp;
			Creatures->ReadCreature(i,temp);

			if(std::string(Materials->raceEx[temp.race].rawname) == "DWARF")
			{
				dwarves.push_back(temp);
			}
			else
			{
				creatures.push_back(temp);
			}
		}		
	//}
}
