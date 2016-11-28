#include"genresmap.h"

GenresMap::GenresMap()
{    
    GMap.insert("sf_history","Альтернативная история");
    GMap.insert("sf_action","Боевая фантастика");
    GMap.insert("sf_epic","Эпическая фантастика");
    GMap.insert("sf_heroic","Героическая фантастика");
    GMap.insert("sf_detective","Детективная фантастика");
    GMap.insert("sf_cyberpunk","Киберпанк");
    GMap.insert("sf_space","Космическая фантастика");
    GMap.insert("sf_social","Социально-психологическая фантастика");
    GMap.insert("sf_horror","Ужасы и Мистика");
    GMap.insert("sf_humor","Юмористическая фантастика");
    GMap.insert("sf_fantasy","Фэнтези");
    GMap.insert("sf","Научная Фантастика");

    GMap.insert("det_classic","Классический детектив");
    GMap.insert("det_police","Полицейский детектив");
    GMap.insert("det_action","Боевик");
    GMap.insert("det_irony","Иронический детектив");
    GMap.insert("det_history","Исторический детектив");
    GMap.insert("det_espionage","Шпионский детектив");
    GMap.insert("det_crime","Криминальный детектив");
    GMap.insert("det_political","Политический детектив");
    GMap.insert("det_maniac","Маньяки");
    GMap.insert("det_hard","Крутой детектив");
    GMap.insert("thriller","Триллер");
    GMap.insert("detective","Детектив");

    GMap.insert("prose_classic","Классическая проза");
    GMap.insert("prose_history","Историческая проза");
    GMap.insert("prose_contemporary","Современная проза");
    GMap.insert("prose_counter","Контркультура");
    GMap.insert("prose_rus_classic","Русская классическая проза");
    GMap.insert("prose_su_classics","Советская классическая проза");

    GMap.insert("love_contemporary","Современные любовные романы");
    GMap.insert("love_history","Исторические любовные романы");
    GMap.insert("love_detective","Остросюжетные любовные романы");
    GMap.insert("love_short","Короткие любовные романы");
    GMap.insert("love_erotica","Эротика");

    GMap.insert("adv_western","Вестерн");
    GMap.insert("adv_history","Исторические приключения");
    GMap.insert("adv_indian","Приключения про индейцев");
    GMap.insert("adv_maritime","Морские приключения");
    GMap.insert("adv_geo","Путешествия и география");
    GMap.insert("adv_animal","Природа и животные");
    GMap.insert("adventure","Приключения");

    GMap.insert("child_tale","Сказка");
    GMap.insert("child_verse","Детские стихи");
    GMap.insert("child_prose","Детскиая проза");
    GMap.insert("child_sf","Детская фантастика");
    GMap.insert("child_det","Детские остросюжетные");
    GMap.insert("child_adv","Детские приключения");
    GMap.insert("child_education","Детская образовательная литература");
    GMap.insert("children","Детская литература");

    GMap.insert("poetry","Поэзия");
    GMap.insert("dramaturgy","Драматургия");

    GMap.insert("antique_ant","Античная литература");
    GMap.insert("antique_european","Европейская старинная литература");
    GMap.insert("antique_russian","Древнерусская литература");
    GMap.insert("antique_east","Древневосточная литература");
    GMap.insert("antique_myths","Мифы. Легенды. Эпос");
    GMap.insert("antique","Старинная литература");

    GMap.insert("sci_history","История");
    GMap.insert("sci_psychology","Психология");
    GMap.insert("sci_culture","Культурология");
    GMap.insert("sci_religion","Религиоведение");
    GMap.insert("sci_philosophy","Философия");
    GMap.insert("sci_politics","Политика");
    GMap.insert("sci_business","Деловая литература");
    GMap.insert("sci_juris","Юриспруденция");
    GMap.insert("sci_linguistic","Языкознание");
    GMap.insert("sci_medicine","Медицина");
    GMap.insert("sci_phys","Физика");
    GMap.insert("sci_math","Математика");
    GMap.insert("sci_chem","Химия");
    GMap.insert("sci_biology","Биология");
    GMap.insert("sci_tech","Технические науки");
    GMap.insert("science","Научная литература");

    GMap.insert("comp_www","Интернет");
    GMap.insert("comp_programming","Программирование");
    GMap.insert("comp_hard","Компьютерное 'железо'");
    GMap.insert("comp_soft","Программы");
    GMap.insert("comp_db","Базы данных");
    GMap.insert("comp_osnet","ОС и Сети");
    GMap.insert("computers","Околокомпьтерная литература");

    GMap.insert("ref_encyc","Энциклопедии");
    GMap.insert("ref_dict","Словари");
    GMap.insert("ref_ref","Справочники");
    GMap.insert("ref_guide","Руководства");
    GMap.insert("reference","Справочная литература");

    GMap.insert("nonf_biography","Биографии и Мемуары");
    GMap.insert("nonf_publicism","Публицистика");
    GMap.insert("nonf_criticism","Критика");
    GMap.insert("design","Искусство и Дизайн");
    GMap.insert("nonfiction","Документальная литература");

    GMap.insert("religion_rel","Религия");
    GMap.insert("religion_esoterics","Эзотерика");
    GMap.insert("religion_self","Самосовершенствование");
    GMap.insert("religion","Религионая литература");

    GMap.insert("humor_anecdote","Анекдоты");
    GMap.insert("humor_prose","Юмористическая проза");
    GMap.insert("humor_verse","Юмористические стихи");
    GMap.insert("humor","Юмор");

    GMap.insert("home_cooking","Кулинария");
    GMap.insert("home_pets","Домашние животные");
    GMap.insert("home_crafts","Хобби и ремесла");
    GMap.insert("home_entertain","Развлечения");
    GMap.insert("home_health","Здоровье");
    GMap.insert("home_garden","Сад и огород");
    GMap.insert("home_diy","Сделай сам");
    GMap.insert("home_sport","Спорт");
    GMap.insert("home_sex","Эротика, Секс");
    GMap.insert("home","Домоводство");
}


QString GenresMap::getGenreFromMap(QString key)
{
    return GMap[key];
}
