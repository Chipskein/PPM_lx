#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <experimental/filesystem>
#include <string>
namespace fs=std::experimental::filesystem;
using namespace std;
string conversor_ot( vector<string>a){
	string b ="";
	for (int i=0;i<=a.size()-1;i++) {
		b = b + a[i] + "\n";
	}
	return b;
}
int main() {
inicio:		
		bool work = false;
		string set_path;
		printf("%s", "_DIR:");
		cin >>set_path;
		fs::path p(set_path);
		while (true){
			if (fs::exists(p)) { cout << set_path << "===>" << "Setado como PATH" << endl; break; }
			else {
				printf("%s\n", "DIR_ERROR");
				printf("%s","NW_DIR:");
				cin >> set_path;
				p = set_path;	
			}
		}
		vector <string> music;
		string string_dr = "DIR:";
		string path_str = p;
		music.push_back(string_dr+path_str);
		for (const auto& entry : fs::directory_iterator(p)) {
			std::string teste;
			teste = entry.path().filename();
			if (entry.path().filename().extension()==".ogg"){
				music.push_back(teste);
			}
		}
		string out="Arquivos .ogg Não Encontrados no PATH";
		if (music.size() != 1) { out =conversor_ot(music); work = true;}
		int cm = 2;
		float vol = 25.5;
		bool pause = false;
		bool mute = false;
		bool help_m = false;
		float pos;
		sf::Font font; font.loadFromFile("fonts/input.ttf");
		sf::Music m;	
		sf::Text t;
			t.setFillColor(sf::Color::Green);
			t.setString(out);
			t.setFont(font);
			t.setCharacterSize(20);
		sf::Text loop_t;
			loop_t.setFillColor(sf::Color::Yellow);
			loop_t.setCharacterSize(20);
			loop_t.setFont(font);
			loop_t.setPosition(40,400);
			loop_t.setString("LOOP:off");
		sf::Text play_t;
			play_t.setFillColor(sf::Color::Yellow);
			play_t.setCharacterSize(20);
			play_t.setFont(font);
			play_t.setPosition(40, 430);
			play_t.setString("PLAY:off");
		sf::Text pause_t;
			pause_t.setFillColor(sf::Color::Yellow);
			pause_t.setCharacterSize(20);
			pause_t.setFont(font);
			pause_t.setPosition(40, 460);
			pause_t.setString("PAUSE:off");

		sf::Text vol_t;
			vol_t.setFillColor(sf::Color::Yellow);
			vol_t.setCharacterSize(20);
			vol_t.setFont(font);
			vol_t.setPosition(360, 400);
			vol_t.setString("VOLUME:0.0");
		sf::Text mute_t;
			mute_t.setFillColor(sf::Color::Yellow);
			mute_t.setCharacterSize(20);
			mute_t.setFont(font);
			mute_t.setPosition(360, 430);
			mute_t.setString("MUTE:off");
		sf::Text time_t;
			time_t.setFillColor(sf::Color::Yellow);
			time_t.setCharacterSize(20);
			time_t.setFont(font);
			time_t.setPosition(360, 460);
			time_t.setString("TIME:00:00:00");
		sf::Text track_t;
			track_t.setFillColor(sf::Color::Red);
			track_t.setCharacterSize(30);
			track_t.setFont(font);
			track_t.setPosition(20, 500);
			track_t.setString("TRACK:");
		sf::Text h_t;
			h_t.setFillColor(sf::Color::Magenta);
			h_t.setCharacterSize(20);
			h_t.setFont(font);
			h_t.setPosition(200,560);
			h_t.setString("Press H to Help");
		sf::Text explic;
			explic.setFillColor(sf::Color::Magenta);
			explic.setCharacterSize(35);
			explic.setFont(font);
			explic.setPosition(150,150);
				string teste = "R=CHANGE_DIR\nPAGEUP=VOLUME+\nPAGEDOWN=VOLUME-\nENTER=PLAY\nSPACE=PAUSE(ON/OFF)\nM=MUTE(ON/OFF)\nL=LOOP(ON/OFF)\nH=HELP(ON/OFF)\n\n~CHIPSKEIN\n";
				explic.setString(teste);
			sf::RectangleShape help_menu(sf::Vector2f(500,500));
				help_menu.setOrigin(250,250);
				help_menu.setFillColor(sf::Color::White);
				help_menu.setPosition(300,300);
			sf::RectangleShape selected(sf::Vector2f(600.0, 20.0));
				selected.setOrigin(300,15);
				selected.setFillColor(sf::Color::White);
	//programa
	sf::RenderWindow window(sf::VideoMode(600, 600), "PPMV2", sf::Style::Close);
	sf::Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());
	while (window.isOpen()) {
		sf::Event e;
		window.clear();
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:	
				if (e.key.code==32 && work){
					switch (pause){
						case true:
							pause = false;
							m.play();
							break;
						case false:
							pause = true;
							m.pause();
							break;
					}
				
				}
				if (e.key.code==108 && work) {
					switch (m.getLoop())
					{
						case true:
							m.setLoop(false);
								loop_t.setString("LOOP:OFF");
							break;
						case false:
							m.setLoop(true);
								loop_t.setString("LOOP:ON");
							break;
						}
				}
				if (e.key.code==109 && work){
					switch (mute){
						case true:
							mute = false;
							break;
						case false:
							mute = true;
							break;
					}
				}
				if (e.key.code == 104){
					switch (help_m)
					{
						case true:
							help_m = false;
							break;
						case false:
							help_m = true;
							break;
					}
				}
				//R-Change dir
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					system("clear");
					goto inicio;
				}
				break;
			}
			//_nav
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && work){
					if (cm >= 2) {
						cm--;
						
					}
					if (cm < 2) {
						cm = music.size();
						
					}

					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && work){
					if (cm <= music.size()) {
						cm++;
						pos = 21.0 * cm;
						selected.setPosition(300, pos);
					}
					if (cm > music.size()) {
						cm = 2;
						
					}
				}
				
			//_vol;
				//-
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) && work) {
					vol--;
					if(vol<0){
						vol = 0;
					}
				}
				//++
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) && work) {
					vol++;
					if(vol>100){
						vol = 100;
						
					}
				}
				//select_play
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)&&work) {
					if (cm != 1) {
						string w = p;
						m.openFromFile(w+"/"+(music[cm-1]));
						m.play();
						string track_l = "TRACK:";
						track_t.setString(track_l+music[cm-1]);
					}
				}
				
		}
		
		pos = 21.0 * cm;
		selected.setPosition(300, pos);
		
		
		if (!mute) {
			m.setVolume(vol);
			mute_t.setString("MUTE:OFF");
		}
		else {
			m.setVolume(0.0);
			mute_t.setString("MUTE:ON");
		}
		//sets_men
			//ons&&offs
			if (m.getStatus()==2) {
				play_t.setString("PLAY:ON");
				pause_t.setString("PAUSE:OFF");
			}
			else if (m.getStatus() == 1) {
				play_t.setString("PLAY:OFF");
				pause_t.setString("PAUSE:ON");
			}
			//vol&time
			vol_t.setString("VOLUME:"+to_string((int)m.getVolume()));
			time_t.setString("TIME:"+to_string(m.getPlayingOffset().asSeconds())+"s");
		if(work){
			window.draw(selected);
		}
		window.draw(t);
		window.draw(loop_t);
		window.draw(mute_t);
		window.draw(time_t);
		window.draw(vol_t);
		window.draw(play_t);
		window.draw(pause_t);
		window.draw(track_t);
		window.draw(h_t);
		if (help_m) {
			window.draw(help_menu);
			window.draw(explic);
		}
		window.display();
	}
}