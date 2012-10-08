/* funcdefs */
funcdef void entThink(cEntity @ent);
funcdef void entTouch(cEntity @ent, cEntity @other, const Vec3 planeNormal, int surfFlags);
funcdef void entUse(cEntity @ent, cEntity @other, cEntity @activator);
funcdef void entPain(cEntity @ent, cEntity @other, float kick, float damage);
funcdef void entDie(cEntity @ent, cEntity @inflicter, cEntity @attacker);
funcdef void entStop(cEntity @ent);

/**
 * cEntity
 */
class cEntity
{
public:
	/* object properties */
	cClient @ client;
	cItem @ item;
	cEntity @ groundEntity;
	cEntity @ owner;
	cEntity @ enemy;
	cEntity @ activator;
	int type;
	int modelindex;
	int modelindex2;
	int frame;
	int ownerNum;
	int counterNum;
	int skinNum;
	int colorRGBA;
	int weapon;
	bool teleported;
	uint effects;
	int sound;
	int team;
	int light;
	const bool inuse;
	uint svflags;
	int solid;
	int clipMask;
	int spawnFlags;
	int style;
	int moveType;
	uint nextThink;
	float health;
	int maxHealth;
	int viewHeight;
	int takeDamage;
	int damage;
	int projectileMaxDamage;
	int projectileMinDamage;
	int projectileMaxKnockback;
	int projectileMinKnockback;
	float projectileSplashRadius;
	int count;
	float wait;
	float delay;
	int waterLevel;
	float attenuation;
	int mass;
	uint timeStamp;
	entThink @ think;
	entTouch @ touch;
	entUse @ use;
	entPain @ pain;
	entDie @ die;
	entStop @ stop;
	int particlesSpeed;
	int particlesShaderIndex;
	int particlesSpread;
	int particlesSize;
	int particlesTime;
	int particlesFrequency;
	bool particlesSpherical;
	bool particlesBounce;
	bool particlesGravity;
	bool particlesExpandEffect;
	bool particlesShrinkEffect;

	/* object behaviors */
	cEntity @ f(); /* factory */ 

	/* object methods */
	Vec3 get_velocity() const;
	void set_velocity(const Vec3 &in);
	Vec3 get_avelocity() const;
	void set_avelocity(const Vec3 &in);
	Vec3 get_origin() const;
	void set_origin(const Vec3 &in);
	Vec3 get_origin2() const;
	void set_origin2(const Vec3 &in);
	Vec3 get_angles() const;
	void set_angles(const Vec3 &in);
	void getSize(Vec3 &out, Vec3 &out);
	void setSize(const Vec3 &in, const Vec3 &in);
	Vec3 get_movedir() const;
	void set_movedir();
	bool isBrushModel() const;
	void freeEntity();
	void linkEntity();
	void unlinkEntity();
	bool isGhosting() const;
	int get_entNum() const;
	int get_playerNum() const;
	String @ get_model() const;
	String @ get_model2() const;
	String @ get_sounds() const;
	String @ get_classname() const;
	String @ get_targetname() const;
	String @ get_target() const;
	String @ get_map() const;
	void set_target( const String &in );
	void set_targetname( const String &in );
	void set_classname( const String &in );
	void set_map( const String &in );
	void ghost();
	void spawnqueueAdd();
	void teleportEffect( bool );
	void respawnEffect();
	void setupModel( const String &in );
	void setupModel( const String &in, const String &in );
	cEntity @ findTargetEntity( const cEntity @from ) const;
	cEntity @ findTargetingEntity( const cEntity @from ) const;
	void useTargets( const cEntity @activator );
	cEntity @ dropItem( int tag ) const;
	void addAIGoal( bool customReach );
	void addAIGoal();
	void removeAIGoal();
	void reachedAIGoal();
	void sustainDamage( cEntity @inflicter, cEntity @attacker, const Vec3 &in dir, float damage, float knockback, float stun, int mod );
	void splashDamage( cEntity @attacker, int radius, float damage, float knockback, float stun, int mod );
	void explosionEffect( int radius );
};

