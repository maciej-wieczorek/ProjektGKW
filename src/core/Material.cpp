#include "Material.h"

Material* Material::emerald;
Material* Material::jade;
Material* Material::obsidian;
Material* Material::pearl;
Material* Material::ruby;
Material* Material::turquoise;
Material* Material::brass;
Material* Material::bronze;
Material* Material::chrome;
Material* Material::copper;
Material* Material::gold;
Material* Material::silver;

std::vector<Material*> Material::materials{};

void Material::initMaterials()
{
	emerald		= new Material("emerald",	glm::vec3(0.0215,0.1745,0.0215),		glm::vec3(0.07568,0.61424,0.07568),		glm::vec3(0.633,0.727811,0.633), 0.6);
	jade		= new Material("jade",		glm::vec3(0.135,0.2225,0.1575),			glm::vec3(0.54,0.89,0.63),				glm::vec3(0.316228,0.316228,0.316228), 0.1);
	obsidian	= new Material("obsidian",	glm::vec3(0.05375,0.05,0.06625),		glm::vec3(0.18275,0.17,0.22525),		glm::vec3(0.332741,0.328634,0.346435), 0.3);
	pearl		= new Material("pearl",		glm::vec3(0.25,0.20725,0.20725),		glm::vec3(1,0.829,0.829),				glm::vec3(0.296648,0.296648,0.296648), 0.088);
	ruby		= new Material("ruby",		glm::vec3(0.1745,0.01175,0.01175),		glm::vec3(0.61424,0.04136,0.04136),		glm::vec3(00.727811,0.626959,0.626959), 0.6);
	turquoise	= new Material("turquoise",	glm::vec3(0.1,0.18725,0.1745),			glm::vec3(0.396,0.74151,0.69102),		glm::vec3(0.297254,0.30829,0.306678), 0.1);
	brass		= new Material("brass",		glm::vec3(0.329412,0.223529,0.027451),	glm::vec3(0.780392,0.568627,0.113725),	glm::vec3(0.992157,0.941176,0.807843), 0.21794872);
	bronze		= new Material("bronze",	glm::vec3(0.2125,0.1275,0.054),			glm::vec3(0.714,0.4284,0.18144),		glm::vec3(0.393548,0.271906,0.166721), 0.2);
	chrome		= new Material("chrome",	glm::vec3(0.25,0.25,0.25),				glm::vec3(0.4,0.4,0.4),					glm::vec3(0.774597,0.774597,0.774597), 0.6);
	copper		= new Material("copper",	glm::vec3(0.19125,0.0735,0.0225),		glm::vec3(0.7038,0.27048,0.0828),		glm::vec3(0.256777,0.137622,0.086014), 0.1);
	gold		= new Material("gold",		glm::vec3(0.24725,0.1995,0.0745),		glm::vec3(0.75164, 0.60648, 0.22648),	glm::vec3(0.628281, 0.555802, 0.366065), 0.4);
	silver		= new Material("silver",	glm::vec3(0.19225,0.19225,0.19225),		glm::vec3(0.50754,0.50754,0.50754),		glm::vec3(0.508273,0.508273,0.508273),0.4);

	materials = std::vector<Material*>{ Material::emerald, Material::jade, Material::obsidian, Material::pearl, Material::ruby,
	Material::turquoise, Material::brass, Material::bronze, Material::chrome, Material::copper, Material::gold, Material::silver
	};
}


Material::Material(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
	name{ name },
	ambient{ ambient },
	diffuse{ diffuse },
	specular{ specular },
	shininess{ shininess }
{
	
}
