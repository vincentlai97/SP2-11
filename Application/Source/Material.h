struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f) 
	{Set(r, g, b);}
	void Set(float r, float g, float b)
	{this->r = r; this->g = g; this->b = b;}
};
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	Material()
	{kAmbient = Component(0.3, 0.3, 0.3); kDiffuse = Component(0.4, 0.4, 0.4); kSpecular = Component(0.2, 0.2, 0.2); kShininess = 3;};
	~Material() {};
};