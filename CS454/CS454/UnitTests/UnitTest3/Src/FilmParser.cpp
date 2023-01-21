#include "../../../Engine/Include/KeyFrameAnimation/FilmParser.h"


std::vector<std::string>films;
std::vector<json>js;

std::vector<SDL_Rect> create_rect(Film_holder f){
    std::vector<SDL_Rect> tmp;
    for(auto it : f.get_frame_arr()){
        SDL_Rect rec{it.x ,it.y , it.w, it.h};
        tmp.push_back(rec);
    }
    return tmp;
}

void print_rects(std::vector<SDL_Rect> re){
    for(auto it :re){
        std::cout << "x:" << it.x << " y:" << it.y << std::endl;
    }
}

bool FilmParser(std::list<AnimationFilm::Data>& output, const std::string& path){
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string find_first_part_path = cwd.string();
    size_t pos = find_first_part_path.find("out");
    std::string half_path = find_first_part_path.substr(0, pos);
    std::string full_asset_path = half_path + "UnitTests\\UnitTest3\\Config";

    std::ifstream f(full_asset_path + "\\data.json");
    json data = json::parse(f);
    for (const auto& item : data.items())
    {
        //std::cout << item.key() << "\n";
         for (const auto& val : item.value().items())
        {
            films.push_back(val.key());
            json j;
            j[val.key()]= val.value();
            js.push_back(j);
        }
    }
    
    JSON_holder holder = JSON_holder();

    
    //std::cout<<js[1].at(films[1]);
    int i =0;
    for(auto f : js){
        std::string key = films[i++];
        json a = f.at(key);
        
        Film_holder f_holder = Film_holder(a,key);
        f_holder.parse_json();    
        holder.add_film(f_holder);
    }

    
   holder.print_for_humans(); 
   std::vector<Film_holder>temp = holder.get_films();

   for(auto it : temp){
       AnimationFilm::Data data = AnimationFilm::Data();
       data.id = it.get_id();
       data.rects = create_rect(it);
       data.path = path + "\\" + it.get_bmp_path();
       output.push_back(data);
   }


 
   return 1;
}