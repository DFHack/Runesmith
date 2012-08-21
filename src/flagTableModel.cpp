#include "flagTableModel.h"

flagTableModel::flagTableModel(QObject *parent) : skillsTableModel(parent, 1)
{
}

flagTableModel::~flagTableModel(void)
{
}

int flagTableModel::rowCount(const QModelIndex &parent) const
{
	if(creature)
	{
		return NUM_FLAGS_SHOWN;
	}
	else
		return 0;
}

QVariant flagTableModel::data(const QModelIndex &index, int role) const
{
	if((!creature) || (!DFI))
		return QVariant();	

	switch(index.column())
	{
	case 0:
		if(role == Qt::DisplayRole)
		{//TODO do this bitwise or something, it's nasty
			//testing found switch faster than function pointer array
			switch(index.row())
			{
			case 0: return "Active Invader";
			case 1: return "Breathing - Good";
			case 2: return "Breathing - Problem";
			case 3: return "Caged";
			case 4: return "Bodyparts Calculated";
			case 5: return "Insulation from Clothing Calculated";
			case 6: return "Calculate Inventory Order";
			case 7: return "Nerves Calculated";
			case 8: return "Can Swap Tiles During Movement";
			case 9: return "Chained";
			case 10: return "Check Flows";
			case 11: return "Circulatory Spray";
			case 12: return "Coward";
			case 13: return "Dead";
			case 14: return "Diplomat";
			case 15: return "Drowning";
			case 16: return "For Trade";
			case 17: return "Merchant/Diplomatic Unit (Likely Leaving)";
			case 18: return "Fortress Guard";
			case 19: return "Gutted";
			case 20: return "Had Mood";
			case 21: return "Has Breaks";
			case 22: return "Has Mood";
			case 23: return "Hidden Ambusher";
			case 24: return "Hidden In Ambush";
			case 25: return "Important Historical Figure (Type 1)";
			case 26: return "Important Historical Figure (Type 2)";
			case 27: return "Incoming";
			case 28: return "Invader - Fleeing/Leaving?";
			case 29: return "Currently Invading";
			case 30: return "Killed";
			case 31: return "Left Map";
			case 32: return "Locked in for Trading";
			case 33: return "Marauder";
			case 34: return "Merchant";
			case 35: return "Can Move (or waiting for timer)";
			case 36: return "Do Not Notify about Level Gains";
			case 37: return "On the Ground";
			case 38: return "Projectile";
			case 39: return "Is Resident";
			case 40: return "Ridden";
			case 41: return "Rider";
			case 42: return "Roaming Wilderness Population Source";
			case 43: return "Roaming Wilderness Population Source - Not Map Feature";
			case 44: return "Royal Guard";
			case 45: return "Skeleton";
			case 46: return "Slaughter";
			case 47: return "Sparring";
			case 48: return "Suppres Wield (for beatings etc)";
			case 49: return "Swimming";
			case 50: return "Tame";
			case 51: return "Trade Resolved";
			case 52: return "Underworld Creautre";
			case 53: return "Vision - Damaged";
			case 54: return "Vision - Good";
			case 55: return "Vision - Missing";
			case 56: return "Visitor";
			case 57: return "Visitor - Uninvited";
			case 58: return "Zombie";
			case 59: return "Vanish Creature (cleanup)";
			case 60: return "Delete Creature (cleanup)";
			case 61: return "Recently Vanished/Deleted";
			case 62: return "Marked for Speacial Cleanup (WARNING!)";
			default: return QVariant();
			}
		}
		else if(role == Qt::CheckStateRole)
		{//testing found switch faster than function pointer array
			DFHack::t_creaturflags1 & flags1 = creature->getFlags1();
			DFHack::t_creaturflags2 & flags2 = creature->getFlags2();

			switch(index.row())
			{
			case 0: return flags1.bits.active_invader ? Qt::Checked : Qt::Unchecked;
			case 1: return flags2.bits.breathing_good ? Qt::Checked : Qt::Unchecked;
			case 2: return flags2.bits.breathing_problem ? Qt::Checked : Qt::Unchecked;
			case 3: return flags1.bits.caged ? Qt::Checked : Qt::Unchecked;
			case 4: return flags2.bits.calculated_bodyparts ? Qt::Checked : Qt::Unchecked;
			case 5: return flags2.bits.calculated_insulation ? Qt::Checked : Qt::Unchecked;
			case 6: return flags2.bits.calculated_inventory ? Qt::Checked : Qt::Unchecked;
			case 7: return flags2.bits.calculated_nerves ? Qt::Checked : Qt::Unchecked;
			case 8: return flags1.bits.can_swap ? Qt::Checked : Qt::Unchecked;
			case 9: return flags1.bits.chained ? Qt::Checked : Qt::Unchecked;
			case 10: return flags1.bits.check_flows ? Qt::Checked : Qt::Unchecked;
			case 11: return flags2.bits.circulatory_spray ? Qt::Checked : Qt::Unchecked;
			case 12: return flags1.bits.coward ? Qt::Checked : Qt::Unchecked;
			case 13: return flags1.bits.dead ? Qt::Checked : Qt::Unchecked;
			case 14: return flags1.bits.diplomat ? Qt::Checked : Qt::Unchecked;
			case 15: return flags1.bits.drowning ? Qt::Checked : Qt::Unchecked;
			case 16: return flags2.bits.for_trade ? Qt::Checked : Qt::Unchecked;
			case 17: return flags1.bits.forest ? Qt::Checked : Qt::Unchecked;
			case 18: return flags1.bits.fortress_guard ? Qt::Checked : Qt::Unchecked;
			case 19: return flags2.bits.gutted ? Qt::Checked : Qt::Unchecked;
			case 20: return flags1.bits.had_mood ? Qt::Checked : Qt::Unchecked;
			case 21: return flags2.bits.has_breaks ? Qt::Checked : Qt::Unchecked;
			case 22: return flags1.bits.has_mood ? Qt::Checked : Qt::Unchecked;
			case 23: return flags1.bits.hidden_ambusher ? Qt::Checked : Qt::Unchecked;
			case 24: return flags1.bits.hidden_in_ambush ? Qt::Checked : Qt::Unchecked;
			case 25: return flags1.bits.important_historical_figure ? Qt::Checked : Qt::Unchecked;
			case 26: return flags2.bits.important_historical_figure ? Qt::Checked : Qt::Unchecked;
			case 27: return flags1.bits.incoming ? Qt::Checked : Qt::Unchecked;
			case 28: return flags1.bits.invader_origin ? Qt::Checked : Qt::Unchecked;
			case 29: return flags1.bits.invades ? Qt::Checked : Qt::Unchecked;
			case 30: return flags2.bits.killed ? Qt::Checked : Qt::Unchecked;
			case 31: return flags1.bits.left ? Qt::Checked : Qt::Unchecked;
			case 32: return flags2.bits.locked_in_for_trading ? Qt::Checked : Qt::Unchecked;
			case 33: return flags1.bits.marauder ? Qt::Checked : Qt::Unchecked;
			case 34: return flags1.bits.merchant ? Qt::Checked : Qt::Unchecked;
			case 35: return flags1.bits.move_state ? Qt::Checked : Qt::Unchecked;
			case 36: return flags2.bits.no_notify ? Qt::Checked : Qt::Unchecked;
			case 37: return flags1.bits.on_ground ? Qt::Checked : Qt::Unchecked;
			case 38: return flags1.bits.projectile ? Qt::Checked : Qt::Unchecked;
			case 39: return flags2.bits.resident ? Qt::Checked : Qt::Unchecked;
			case 40: return flags1.bits.ridden ? Qt::Checked : Qt::Unchecked;
			case 41: return flags1.bits.rider ? Qt::Checked : Qt::Unchecked;
			case 42: return flags2.bits.roaming_wilderness_population_source ? Qt::Checked : Qt::Unchecked;
			case 43: return flags2.bits.roaming_wilderness_population_source_not_a_map_feature ? Qt::Checked : Qt::Unchecked;
			case 44: return flags1.bits.royal_guard ? Qt::Checked : Qt::Unchecked;
			case 45: return flags1.bits.skeleton ? Qt::Checked : Qt::Unchecked;
			case 46: return flags2.bits.slaughter ? Qt::Checked : Qt::Unchecked;
			case 47: return flags2.bits.sparring ? Qt::Checked : Qt::Unchecked;
			case 48: return flags1.bits.suppress_wield ? Qt::Checked : Qt::Unchecked;
			case 49: return flags2.bits.swimming ? Qt::Checked : Qt::Unchecked;
			case 50: return flags1.bits.tame ? Qt::Checked : Qt::Unchecked;
			case 51: return flags2.bits.trade_resolved ? Qt::Checked : Qt::Unchecked;
			case 52: return flags2.bits.underworld ? Qt::Checked : Qt::Unchecked;
			case 53: return flags2.bits.vision_damaged ? Qt::Checked : Qt::Unchecked;
			case 54: return flags2.bits.vision_good ? Qt::Checked : Qt::Unchecked;
			case 55: return flags2.bits.vision_missing ? Qt::Checked : Qt::Unchecked;
			case 56: return flags2.bits.visitor ? Qt::Checked : Qt::Unchecked;
			case 57: return flags2.bits.visitor_uninvited ? Qt::Checked : Qt::Unchecked;
			case 58: return flags1.bits.zombie ? Qt::Checked : Qt::Unchecked;
			case 59: return flags2.bits.cleanup_1 ? Qt::Checked : Qt::Unchecked;
			case 60: return flags2.bits.cleanup_2 ? Qt::Checked : Qt::Unchecked;
			case 61: return flags2.bits.cleanup_3 ? Qt::Checked : Qt::Unchecked;
			case 62: return flags2.bits.cleanup_4 ? Qt::Checked : Qt::Unchecked;
			default: return Qt::Unchecked;
			}
		}
		else
			return QVariant();

	default:
		return QVariant();
	}
}

QVariant flagTableModel::headerData(int section,
									Qt::Orientation orientation,
									int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return QString("Flags");	

		default:
			return QVariant();
		}
	}
	else
		return QVariant();
}

Qt::ItemFlags flagTableModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;
	
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;	
}

bool flagTableModel::setData(const QModelIndex &index,
							 const QVariant &value, 
							 int role)
{
	if(index.column())
		return false;

	uint32_t temp = value.toUInt();
	DFHack::t_creaturflags1 & flags1 = creature->getFlags1();
	DFHack::t_creaturflags2 & flags2 = creature->getFlags2();

	switch(index.row())
	{
	case 0: flags1.bits.active_invader = temp ? 1 : 0; break;
	case 1: flags2.bits.breathing_good = temp ? 1 : 0; break;
	case 2: flags2.bits.breathing_problem = temp ? 1 : 0; break;
	case 3: flags1.bits.caged = temp ? 1 : 0; break;
	case 4: flags2.bits.calculated_bodyparts = temp ? 1 : 0; break;
	case 5: flags2.bits.calculated_insulation = temp ? 1 : 0; break;
	case 6: flags2.bits.calculated_inventory = temp ? 1 : 0; break;
	case 7: flags2.bits.calculated_nerves = temp ? 1 : 0; break;
	case 8: flags1.bits.can_swap = temp ? 1 : 0; break;
	case 9: flags1.bits.chained = temp ? 1 : 0; break;
	case 10: flags1.bits.check_flows = temp ? 1 : 0; break;
	case 11: flags2.bits.circulatory_spray = temp ? 1 : 0; break;
	case 12: flags1.bits.coward = temp ? 1 : 0; break;
	case 13: flags1.bits.dead = temp ? 1 : 0; break;
	case 14: flags1.bits.diplomat = temp ? 1 : 0; break;
	case 15: flags1.bits.drowning = temp ? 1 : 0; break;
	case 16: flags2.bits.for_trade = temp ? 1 : 0; break;
	case 17: flags1.bits.forest = temp ? 1 : 0; break;
	case 18: flags1.bits.fortress_guard = temp ? 1 : 0; break;
	case 19: flags2.bits.gutted = temp ? 1 : 0; break;
	case 20: flags1.bits.had_mood = temp ? 1 : 0; break;
	case 21: flags2.bits.has_breaks = temp ? 1 : 0; break;
	case 22: flags1.bits.has_mood = temp ? 1 : 0; break;
	case 23: flags1.bits.hidden_ambusher = temp ? 1 : 0; break;
	case 24: flags1.bits.hidden_in_ambush = temp ? 1 : 0; break;
	case 25: flags1.bits.important_historical_figure = temp ? 1 : 0; break;
	case 26: flags2.bits.important_historical_figure = temp ? 1 : 0; break;
	case 27: flags1.bits.incoming = temp ? 1 : 0; break;
	case 28: flags1.bits.invader_origin = temp ? 1 : 0; break;
	case 29: flags1.bits.invades = temp ? 1 : 0; break;
	case 30: flags2.bits.killed = temp ? 1 : 0; break;
	case 31: flags1.bits.left = temp ? 1 : 0; break;
	case 32: flags2.bits.locked_in_for_trading = temp ? 1 : 0; break;
	case 33: flags1.bits.marauder = temp ? 1 : 0; break;
	case 34: flags1.bits.merchant = temp ? 1 : 0; break;
	case 35: flags1.bits.move_state = temp ? 1 : 0; break;
	case 36: flags2.bits.no_notify = temp ? 1 : 0; break;
	case 37: flags1.bits.on_ground = temp ? 1 : 0; break;
	case 38: flags1.bits.projectile = temp ? 1 : 0; break;
	case 39: flags2.bits.resident = temp ? 1 : 0; break;
	case 40: flags1.bits.ridden = temp ? 1 : 0; break;
	case 41: flags1.bits.rider = temp ? 1 : 0; break;
	case 42: flags2.bits.roaming_wilderness_population_source = temp ? 1 : 0; break;
	case 43: flags2.bits.roaming_wilderness_population_source_not_a_map_feature = temp ? 1 : 0; break;
	case 44: flags1.bits.royal_guard = temp ? 1 : 0; break;
	case 45: flags1.bits.skeleton = temp ? 1 : 0; break;
	case 46: flags2.bits.slaughter = temp ? 1 : 0; break;
	case 47: flags2.bits.sparring = temp ? 1 : 0; break;
	case 48: flags1.bits.suppress_wield = temp ? 1 : 0; break;
	case 49: flags2.bits.swimming = temp ? 1 : 0; break;
	case 50: flags1.bits.tame = temp ? 1 : 0; break;
	case 51: flags2.bits.trade_resolved = temp ? 1 : 0; break;
	case 52: flags2.bits.underworld = temp ? 1 : 0; break;
	case 53: flags2.bits.vision_damaged = temp ? 1 : 0; break;
	case 54: flags2.bits.vision_good = temp ? 1 : 0; break;
	case 55: flags2.bits.vision_missing = temp ? 1 : 0; break;
	case 56: flags2.bits.visitor = temp ? 1 : 0; break;
	case 57: flags2.bits.visitor_uninvited = temp ? 1 : 0; break;
	case 58: flags1.bits.zombie = temp ? 1 : 0; break;
	case 59: flags2.bits.cleanup_1 = temp ? 1 : 0; break;
	case 60: flags2.bits.cleanup_2 = temp ? 1 : 0; break;
	case 61: flags2.bits.cleanup_3 = temp ? 1 : 0; break;
	case 62: flags2.bits.cleanup_4 = temp ? 1 : 0; break;
	default: return false;
	}

	creature->setFlagsChanged();
	return true;
}
