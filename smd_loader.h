#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>

struct smd_triangle_s
{
    int parent_bone;
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    int links;
    int bone_id;

    smd_triangle_s() :
        parent_bone(-1),
        position(glm::vec3(0.0f)),
        normal(glm::vec3(0.0f)),
        uv(glm::vec2(0.0f)),
        links(-1),
        bone_id(-1)
    {
    }

    smd_triangle_s(int parent_bone, glm::vec3 position, glm::vec3 normal, glm::vec2 uv, int links, int bone_id) :
        parent_bone(parent_bone),
        position(position),
        normal(normal),
        uv(uv),
        links(links),
        bone_id(bone_id)
    {
    }
};

struct smd_bone_s
{
    int id;
    std::pmr::string name;
    int parent_id;

    smd_bone_s() :
        id(-1),
        name(""),
        parent_id(-1)
    {
    }

    smd_bone_s(int id, std::pmr::string name, int parent_id) :
        id(id),
        name(name),
        parent_id(parent_id)
    {
    }
};

struct smd_frame_s
{
    int id;
    glm::vec3 position;
    glm::vec3 rotation;

    smd_frame_s() : id(-1), position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f))
    {
    }

    smd_frame_s(int id, glm::vec3 position, glm::vec3 rotation) :
        id(id),
        position(position),
        rotation(rotation)
    {
    }
};

enum smd_load_state_e
{
    CONTINUE,
    HEADER,
    BONE,
    ANIMATION,
    MESH
};

struct smd_s
{
    int version{};
    std::vector<smd_triangle_s> triangles;
    std::vector<smd_bone_s> bones;
    std::vector<smd_frame_s> frames;

    explicit smd_s(const std::string& filename)
    {
        this->version = -1;
        this->triangles = std::vector<smd_triangle_s>();
        this->bones = std::vector<smd_bone_s>();
        this->frames = std::vector<smd_frame_s>();

        load(filename);
    }

private:
    void load(const std::string& filename)
    {
        std::vector<std::string> lines;

        if (!filename.empty())
        {
            std::ifstream file;

            file.open(filename, std::ios::in);

            if (!file.is_open())
            {
                std::cerr << "Could not open file " << std::endl;
            }

            std::string line;
            while (std::getline(file, line))
            {
                if (!line.empty())
                {
                    lines.push_back(line);
                }
            }

            file.close();
        }

        for (std::string line : lines)
        {
            smd_load_state_e state = get_load_state(line);
            switch (state)
            {
            case HEADER:
                load_version(line);
                continue;
            case BONE:
                load_bones(line);
                continue;
            case ANIMATION:
                load_animation(line);
                continue;
            case MESH:
                load_trangles(line);
                continue;
            case CONTINUE:
                continue;
            default:
                continue;
            }
        }
    }

    void load_version(std::string line)
    {
        this->version = 0;
    }

    void load_trangles(std::string line)
    {
    }

    void load_bones(std::string line)
    {
    }

    void load_animation(std::string line)
    {
    }

    std::vector<std::string> cut_to_items(const std::string& line, const char separator)
    {
        std::vector<std::string> result;

        return result;
    }

    smd_load_state_e get_load_state(const std::string& line)
    {
        int pos = 0;

        pos = line.find_first_of("//");
        if (pos == 0)
        {
            return CONTINUE;
        }

        pos = line.find_first_of("version");
        if (pos == 0)
        {
            return HEADER;
        }

        return CONTINUE;
    }
};
