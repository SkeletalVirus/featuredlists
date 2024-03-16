#include <Geode/modify/ProfilePage.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <iostream>

using namespace geode::prelude;

class $modify(MyProfilePage, ProfilePage) {
    void loadPageFromUserInfo(GJUserScore* a2){

		GameLevelManager::sharedState()->storeUserName(a2->m_userID, a2->m_accountID, a2->m_userName);
        ProfilePage::loadPageFromUserInfo(a2);

		if(auto menu = m_mainLayer->getChildByID("left-menu")) {

		auto btnTexture = Mod::get()->getSettingValue<int64_t>("btn_texture");

		
		auto listBtnSprite = CCSprite::createWithSpriteFrameName("GJ_viewListsBtn_001.png");
	
			switch(btnTexture)
			{
				case 1: listBtnSprite = CCSprite::create("demonBtn.png"_spr);
				break;

				case 2: listBtnSprite = CCSprite::create("trophyBtn.png"_spr);
				break;

				case 3: listBtnSprite = CCSprite::create("cpBtn.png"_spr);
				break; 

				case 4: listBtnSprite = CCSprite::create("starBtn.png"_spr);
				break;

				default: listBtnSprite = CCSprite::createWithSpriteFrameName("GJ_viewListsBtn_001.png");
				break;
			}
			
			auto listBtn = CCMenuItemSpriteExtra::create(
				listBtnSprite,
				this,
				menu_selector(MyProfilePage::onListButton)
				);

			listBtn->setID("test-button"_spr);
				menu->addChild(listBtn);
				this->m_buttons->addObject(listBtn);
					listBtn->setZOrder(1);
					listBtnSprite->setScale(0.75);
					listBtn->setScale(0.75);
			menu->updateLayout();


		} else {
			FLAlertLayer::create(
				"Error",
				"Featured List could not be loaded",
				"OK"
			)->show();
		}
    }

public:
	void onListButton(CCObject* sender) {	
		auto listID = Mod::get()->getSettingValue<int64_t>("list_id");
		if(listID > 0) {
			
		std::string listIDString = std::to_string(listID);

		auto obj = GJSearchObject::create(SearchType::Search, listIDString);
		obj->m_searchMode = 1; //1 for lists, 0 for levels
		auto browser = LevelBrowserLayer::create(obj);
		switchToScene(browser);

		} else if(listID < 0) {
		int newListID = listID * -1;

		std::string listIDString = std::to_string(newListID);

		auto obj = GJSearchObject::create(SearchType::Search, listIDString);
		obj->m_searchMode = 1; //1 for lists, 0 for levels
		auto browser = LevelBrowserLayer::create(obj);
		switchToScene(browser);

		} else if(listID == 0) {
			geode::createQuickPopup(
				"Error",
				"No List ID has been set! \n Please set a List ID in the <cy>Mod Settings</c>! \n \n Would you like to open <cy>Mod Settings</c>?",
				"No", "Yes",
				[](auto, bool btn2) {
					if (btn2){
						geode::openSettingsPopup(Mod::get());
					}
				}
			);
		}
	};

};