#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../../../ThirdParty/json.hpp"
#include "AnimationFilm.h"
#include "SDL.h"

// for convenience
using json = nlohmann::json;
class Film_holder {
private:
    std::string id;
    std::string bmp_path;
    json j_format;
    typedef struct {
        int h, w, x, y;

    }frame;
    std::vector<frame> frame_arr;

public:
    Film_holder(json j_insert, std::string key) :j_format{ j_insert }, id{ key } {}
    std::vector<frame> get_frame_arr(){
        return frame_arr;
    }
    json get_json() {
        return j_format;
    }

    void parse_json() {
        json arr;
        for (auto& it : j_format.items()) {

            for (auto& a : it.value().items()) {
                if (a.key() == "frames") {
                    arr = a;
                }
                else if (a.key() == "bmp") {
                    bmp_path = a.value();
                }
            }
        }
        initialize_array(arr);
    }


    void initialize_array(json array) {
        std::vector<int>buffer;
        for (auto& it : array) {
            for (auto& item : it.items()) {
                for (auto& i : item.value().items()) {

                    buffer.push_back(i.value().get<int>());
                }
                frame f{ buffer[0],buffer[1],buffer[2],buffer[3] };
                frame_arr.push_back(f);
                buffer.clear();
            }
        }

    }
    std::string get_id() {
        return id;
    }
    std::string get_bmp_path() {
        return bmp_path;
    }

    void print_frame_array() {
        for (auto it : frame_arr) {
            std::cout << "h:" << it.h << " w:" << it.w << " x" << it.x << " y" << it.y << std::endl;
        }
    }
};



class JSON_holder final {
private:
    using f_vector = std::vector<Film_holder>;
    f_vector films;
public:
    void add_film(Film_holder film) {
        films.push_back(film);
    }

    f_vector get_films() {
        return films;
    }
    void print_for_humans() {
        for (auto it : films) {
            std::cout << "FILM ID:" << it.get_id() << "\n" << "FILM DATA:\n";
            it.print_frame_array();
            std::cout << "BMP PATH:" << it.get_bmp_path() << std::endl;
        }
    }

};


bool FilmParser(std::list<AnimationFilm::Data>& output, const std::string& path);