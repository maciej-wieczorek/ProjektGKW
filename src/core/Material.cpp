#include "Material.h"

Material* Material::gold;

void Material::initMaterials()
{
	gold = new Material(
		glm::vec3(0.24725, 0.1995, 0.0745),
		glm::vec3(0.75164, 0.60648, 0.22648),
		glm::vec3(0.628281, 0.555802, 0.366065),
		0.4
	);
}


Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
	ambient{ ambient },
	diffuse{ diffuse },
	specular{ specular },
	shininess{ shininess }
{
	
}
