#include "../Include/KeyFrameAnimation/FilmParser.h"


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

bool FilmParser(std::list<AnimationFilm::Data>& output,std::string path){ 
    
    std::ifstream f(path +"\\conf\\"+"\\config.json");
    json data = json::parse(f);
    for (const auto& item : data["engine"]["Films"].items())
    {
         for (const auto& val : item.value().items())
        {
             
            films.push_back(val.key());
            json j;
            j[val.key()]= val.value();
            js.push_back(j);
        }
    }
    
    JSON_holder holder = JSON_holder();
    int i =0;
    for(auto f : js){
        std::string key = films[i++];
        json a = f.at(key);
        
        Film_holder f_holder = Film_holder(a,key);
        f_holder.parse_json();    
        holder.add_film(f_holder);
    }

    
   //holder.print_for_humans(); 
   
   std::vector<Film_holder>temp = holder.get_films();

   for(auto it : temp){
       AnimationFilm::Data data = AnimationFilm::Data();
       data.id = it.get_id();
       data.rects = create_rect(it);
       data.path = path + "\\UnitTest3Media\\" + it.get_bmp_path();
       output.push_back(data);
   }
   

   f.close();
   return 1;
}