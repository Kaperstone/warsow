/* funcdefs */

/**
 * cItem
 */
class cItem
{
public:
	/* object properties */
	const int tag;
	const uint type;
	const int flags;
	const int quantity;
	const int inventoryMax;
	const int ammoTag;
	const int weakAmmoTag;

	/* object behaviors */
	cItem@ f(); /* factory */ 

	/* object methods */
	String @ get_classname() const;
	String @ get_name() const;
	String @ get_shortName() const;
	String @ get_model() const;
	String @ get_model2() const;
	String @ get_icon() const;
	String @ get_simpleIcon() const;
	String @ get_pickupSound() const;
	String @ get_colorToken() const;
	bool isPickable() const;
	bool isUsable() const;
	bool isDropable() const;
};

