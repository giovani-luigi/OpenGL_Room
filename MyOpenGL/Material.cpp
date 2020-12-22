#include "Material.h"

Material::Material(const glm::vec3& specular, const glm::vec3& diffuse, const glm::vec3& ambient, float shininess) :
    m_specular(specular),
    m_diffuse(diffuse),
    m_ambient(ambient),
    m_shininess(shininess),
    m_texture()
{
}

void Material::use(Shader& shader)
{
    shader.use();
    shader.setVec3("u_material.specular", m_specular.r, m_specular.g, m_specular.b); // material specular reflection
    shader.setVec3("u_material.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b); // material diffuse reflection
    shader.setVec3("u_material.ambient", m_ambient.r, m_ambient.g, m_ambient.b); // material ambient reflection
    shader.setFloat("u_material.shininess", m_shininess);
        
    shader.setInt("u_material.texture_unit", 0);

    if (has_texture())
    {
        shader.setBool("u_material.has_texture", true);
        m_texture.use();
    }
    else
    {
        shader.setBool("u_material.has_texture", false);
    }
}

Material Material::create_default()
{
    return Material(
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        4
    );
}

Material Material::create_white_marble()
{
    return Material(
        glm::vec3(1.0f, 0.97f, 0.98f),
        glm::vec3(0.5f, 0.45f, 0.38f),
        glm::vec3(0.75f, 0.75f, 0.75f),
        32
    );
}

Material Material::create_brown_floor()
{
    return Material(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.2f, 0.12f, 0.1f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        0
    );
}

Material Material::create_night_floor()
{
    return Material(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.07f, 0.07f, 0.07f),
        glm::vec3(0.05f, 0.07f, 0.10f),
        0
    );
}

Material Material::create_dark_grey_rock()
{
    return Material(
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        0
    );
}

Material Material::create_yellow_rock()
{
    return Material(
        glm::vec3(0.12f, 0.11f, 0.1f),
        glm::vec3(0.6f, 0.5f, 0.4f),
        glm::vec3(0.2f, 0.2f, 0.15f),
        4
    );
}

Material Material::create_texture(
    const vector<float>& coordinates, 
    const std::string& imagePath, 
    const glm::vec3& ambient, 
    const glm::vec3& diffuse, 
    const glm::vec3& specular, 
    float shininess)
{
    auto m = Material(specular, diffuse, ambient, shininess);
    m.m_texture = Texture(imagePath, true);
    m.m_texcoordinates = coordinates;
    return m;
}
