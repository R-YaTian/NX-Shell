#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <glad/glad.h>
#include <cstdio>
#include <memory>
#include <switch.h>

#include "config.hpp"
#include "gui.hpp"
#include "imgui_impl_switch.hpp"
#include "log.hpp"

namespace GUI {
    static EGLDisplay s_display = EGL_NO_DISPLAY;
    static EGLContext s_context = EGL_NO_CONTEXT;
    static EGLSurface s_surface = EGL_NO_SURFACE;
    
    static bool InitEGL(NWindow* win) {
        s_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        
        if (!s_display) {
            Log::Error("Could not connect to display! error: %d", eglGetError());
            return false;
        }
        
        eglInitialize(s_display, nullptr, nullptr);
        
        if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE) {
            Log::Error("Could not set API! error: %d", eglGetError());
            eglTerminate(s_display);
            s_display = nullptr;
        }
        
        EGLConfig config;
        EGLint num_configs;
        static const EGLint framebuffer_attr_list[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
            EGL_RED_SIZE,     8,
            EGL_GREEN_SIZE,   8,
            EGL_BLUE_SIZE,    8,
            EGL_ALPHA_SIZE,   8,
            EGL_DEPTH_SIZE,   24,
            EGL_STENCIL_SIZE, 8,
            EGL_NONE
        };
        
        eglChooseConfig(s_display, framebuffer_attr_list, std::addressof(config), 1, std::addressof(num_configs));
        if (num_configs == 0) {
            Log::Error("No config found! error: %d", eglGetError());
            eglTerminate(s_display);
            s_display = nullptr;
        }
        
        s_surface = eglCreateWindowSurface(s_display, config, win, nullptr);
        if (!s_surface) {
            Log::Error("Surface creation failed! error: %d", eglGetError());
            eglTerminate(s_display);
            s_display = nullptr;
        }
        
        static const EGLint context_attr_list[] = {
            EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
            EGL_CONTEXT_MAJOR_VERSION_KHR, 4,
            EGL_CONTEXT_MINOR_VERSION_KHR, 3,
            EGL_NONE
        };
        
        s_context = eglCreateContext(s_display, config, EGL_NO_CONTEXT, context_attr_list);
        if (!s_context) {
            Log::Error("Context creation failed! error: %d", eglGetError());
            eglDestroySurface(s_display, s_surface);
            s_surface = nullptr;
        }
        
        eglMakeCurrent(s_display, s_surface, s_surface, s_context);
        return true;
    }
    
    static void ExitEGL(void) {
        if (s_display) {
            eglMakeCurrent(s_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            
            if (s_context) {
                eglDestroyContext(s_display, s_context);
                s_context = nullptr;
            }
            
            if (s_surface) {
                eglDestroySurface(s_display, s_surface);
                s_surface = nullptr;
            }
            
            eglTerminate(s_display);
            s_display = nullptr;
        }
    }

    bool SwapBuffers(void) {
        return eglSwapBuffers(s_display, s_surface);
    }

    void SetDefaultTheme(void) {
        ImGui::GetStyle().FrameRounding = 4.0f;
        ImGui::GetStyle().GrabRounding = 4.0f;
        
        ImVec4 *colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.00f, 0.50f, 0.50f, 1.0f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

    bool Init(void) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        
        if (!GUI::InitEGL(nwindowGetDefault()))
            return false;
        
        gladLoadGL();
        
        ImGui_ImplSwitch_Init("#version 130");
        
        // Load nintendo font
        PlFontData standard, extended, schinese, korean, tchinese;
        static ImWchar extended_range[] = {0xE000, 0xE152};
        
        if (R_SUCCEEDED(plGetSharedFontByType(std::addressof(standard), PlSharedFontType_Standard)) &&
            R_SUCCEEDED(plGetSharedFontByType(std::addressof(extended), PlSharedFontType_NintendoExt)) &&
            R_SUCCEEDED(plGetSharedFontByType(std::addressof(schinese), PlSharedFontType_ChineseSimplified)) &&
            R_SUCCEEDED(plGetSharedFontByType(std::addressof(tchinese), PlSharedFontType_ChineseTraditional)) &&
            R_SUCCEEDED(plGetSharedFontByType(std::addressof(korean), PlSharedFontType_KO))) {
                
            u8 *px = nullptr;
            int w = 0, h = 0, bpp = 0;
            ImFontConfig font_cfg;
            
            font_cfg.FontDataOwnedByAtlas = false;
            io.Fonts->AddFontFromMemoryTTF(standard.address, standard.size, 20.f, std::addressof(font_cfg), io.Fonts->GetGlyphRangesDefault());

            if (cfg.multi_lang) {
                font_cfg.MergeMode = true;
                io.Fonts->AddFontFromMemoryTTF(extended.address, extended.size, 20.f, std::addressof(font_cfg), extended_range);
                io.Fonts->AddFontFromMemoryTTF(korean.address, korean.size,   20.f, std::addressof(font_cfg), io.Fonts->GetGlyphRangesKorean());
                if (cfg.full_charset)
                    io.Fonts->AddFontFromMemoryTTF(schinese.address, schinese.size,   20.f, std::addressof(font_cfg), io.Fonts->GetGlyphRangesChineseFull());
                else {
                    io.Fonts->AddFontFromMemoryTTF(schinese.address, schinese.size,   20.f, std::addressof(font_cfg), io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
                    static unsigned char buff[] = {"復製瀏誌阿啊哀唉挨矮愛礙安岸按案暗昂襖傲奧八巴扒吧疤拔把壩爸罷霸白百柏擺敗拜班般斑搬板版吧疤拔把壩爸罷霸白百柏擺敗拜班般斑搬板版辦半伴扮拌瓣幫綁榜膀傍棒包胞雹寶飽保堡報抱暴爆杯悲碑北貝備背倍被輩奔本笨蹦逼鼻比彼筆鄙幣必畢閉斃弊碧蔽壁避臂邊編鞭扁便變遍辨辯辮標表別賓濱冰兵丙柄餅並病撥波玻剝脖菠播伯駁泊博搏膊薄蔔補捕不布步怖部擦猜才材財裁采彩睬踩菜參餐殘蠶慚慘燦倉蒼艙藏操槽草冊側廁測策層叉插查茶察岔差拆柴饞纏產鏟顫昌長腸嘗償常廠場敞暢倡唱抄鈔超朝潮吵炒車扯徹撤塵臣沉辰陳晨闖襯稱趁撐成呈承池匙尺齒恥斥赤翅充沖誠城乘懲程秤吃馳遲持臭出初除廚鋤礎儲楚處蟲崇抽仇綢愁稠籌酬醜觸畜川穿傳船喘串瘡窗床創吹炊垂錘春純唇蠢聰叢湊粗促醋竄催摧脆詞慈辭磁此次刺從匆蔥大呆代帶待怠貸袋逮戴翠村存寸錯曾搭達答打蛋當擋黨蕩檔刀叨導島丹單擔耽膽旦但誕彈淡倒蹈到悼盜道稻得德的燈登等凳低堤滴敵笛底抵地弟帝遞第顛典點電店墊殿叼雕吊釣調掉爹跌疊蝶丁叮盯釘頂訂定丟東冬董懂動凍棟洞都鬥抖陡豆逗督毒讀獨堵賭杜肚度渡端短段斷緞朵躲惰鵝蛾額惡餓恩兒鍛堆隊對噸蹲盾頓多奪而耳二發乏伐罰閥法帆番翻凡煩繁反返犯泛飯範販方坊芳防妨房仿訪紡放飛非肥匪廢沸肺費分吩紛芬墳粉份奮憤糞豐風封瘋峰鋒蜂逢縫諷鳳奉佛否夫膚伏扶服俘浮符幅福撫府斧俯輔腐父付婦負附咐複赴副傅富腹覆該改蓋溉概幹甘綱缸鋼港杠高膏糕搞稿杆肝竿稈趕敢感岡剛崗葛隔個各給根跟更耕工告哥胳鴿割擱歌閣革格弓公功攻供宮恭躬鞏共貢勾溝鉤狗構購夠估姑孤辜古穀股骨鼓固故顧瓜刮掛乖拐怪關觀官冠館管貫慣灌罐光廣歸龜規軌鬼櫃貴桂跪滾棍鍋國果裹過哈孩海害含寒喊漢汗旱航毫豪好號浩賀黑痕很狠恨恒橫衡轟耗喝禾合何和河核荷盒哄烘紅宏洪虹喉猴吼後厚候乎呼忽狐胡壺湖糊化劃畫話懷槐壞歡還環蝴虎互戶護花華嘩滑猾晃謊灰恢揮輝回悔匯會緩幻喚換患荒慌皇黃煌活火夥或貨獲禍惑擊饑繪賄惠毀慧昏婚渾魂混吉級即極急疾集籍幾己圾機肌雞跡積基績激及既濟繼寄加夾佳家嘉甲擠脊計記紀忌技際劑季間肩艱兼監煎揀儉繭撿價駕架假嫁稼奸尖堅殲健艦漸踐鑒鍵箭江薑將減剪檢簡見件建劍薦賤郊嬌澆驕膠椒焦蕉角狡漿僵疆講獎槳匠降醬交皆接揭街節劫傑潔結捷絞餃腳攪繳叫轎較教階今斤金津筋僅緊謹錦盡截竭姐解介戒屆界借巾晶睛精井頸景警淨徑競勁近進晉浸禁京經莖驚酒舊救就舅居拘鞠局菊竟敬境靜鏡糾究揪九久橘舉矩句巨拒具俱劇懼據距鋸聚捐卷倦絹決絕覺掘嚼軍君均菌俊卡開凱慨刊堪砍看康糠扛抗炕考烤靠科棵顆殼咳可渴克刻客課肯墾懇坑空孔恐控口扣寇枯哭苦庫褲酷誇垮挎跨塊快寬款筐狂況曠礦框虧葵愧昆捆困擴括闊垃拉啦喇臘懶爛濫郎狼廊朗浪撈勞蠟辣來賴蘭攔欄藍籃覽累冷厘梨狸離犁鸝璃黎牢老姥澇樂勒雷壘淚類勵例隸栗粒倆連簾憐蓮禮李裡理力曆厲立麗利梁糧粱兩亮諒輛量遼療聯廉鐮臉練煉戀鏈良涼臨淋伶靈嶺鈴陵零齡領僚了料列劣烈獵裂鄰林籠聾隆壟攏樓摟漏露蘆令另溜劉流留榴柳六龍旅屢律慮率綠卵亂掠略爐虜魯陸錄鹿濾碌路驢落媽麻馬碼螞罵嗎埋買輪論羅蘿鑼籮騾螺絡駱忙芒盲茫貓毛矛茅茂冒邁麥賣脈蠻饅瞞滿慢漫美妹門悶們萌盟猛蒙孟貿帽貌麼沒眉梅煤黴每棉免勉面苗描秒妙廟滅夢迷謎米眯秘密蜜眠綿摩磨魔抹末沫莫漠墨默蔑民敏名明鳴命摸模膜暮拿哪內那納乃奶耐男謀某母畝木目牧墓幕慕尼泥你逆年念娘釀鳥尿南難囊撓惱腦鬧呢嫩能奴努怒女暖挪歐偶辟趴捏您寧凝牛扭紐農濃弄乓旁胖拋炮袍跑泡陪培爬怕拍牌派攀盤判叛盼碰批披劈皮疲脾匹僻片賠佩配噴盆朋棚蓬膨捧乒平評憑蘋瓶萍坡潑婆偏篇騙漂飄票撇拼貧品譜七妻戚期欺漆齊其奇迫破魄剖僕撲鋪葡樸普汽砌器恰洽千遷牽鉛謙騎棋旗乞企豈啟起氣棄腔強牆搶悄敲鍬喬僑橋簽前錢鉗潛淺遣欠歉槍禽勤青輕傾清蜻情晴頃瞧巧切茄且竊親侵芹琴屈趨渠取去趣圈全權泉請慶窮丘秋求球區曲驅群然燃染嚷壤讓饒擾繞拳犬勸券缺卻雀確鵲裙日絨榮容熔融柔揉肉如惹熱人仁忍刃認任扔仍乳辱入軟銳瑞潤若弱撒灑塞賽三傘散桑嗓喪掃刪衫閃陝扇善傷商裳晌嫂色森殺沙紗傻篩曬山哨舌蛇舍設社射涉攝申賞上尚捎梢燒稍勺少紹慎升生聲牲勝繩省聖盛伸身深神沈審嬸腎甚滲石時識實拾蝕食史使始剩屍失師詩施獅濕十什視試飾室是柿適逝釋誓駛士氏世市示式事侍勢書叔殊梳疏舒輸蔬熟暑收手守首壽受獸售授瘦耍衰摔甩帥拴雙霜爽誰鼠屬薯術束述樹豎數刷斯撕死四寺似飼肆松宋水稅睡順說嗽絲司私思速宿塑酸蒜算雖隨歲碎誦送頌搜艘蘇俗訴肅素它塌塔踏台抬太態泰貪穗孫損筍縮所索鎖她他攤灘壇談痰毯歎炭探鍛堆隊對噸蹲盾頓多奪濤掏滔逃桃陶淘萄討套湯唐堂塘膛糖倘躺燙趟惕替天添田甜填挑條跳特疼騰梯踢提題蹄體剃通同桐銅童統桶筒痛偷貼鐵帖廳聽亭庭停挺艇土吐兔團推腿退吞屯托頭投透禿突圖徒塗途屠外彎灣丸完玩頑挽晚碗拖脫駝妥娃挖蛙瓦襪歪危威微為圍違唯維偉偽萬汪亡王網往妄忘旺望溫文紋聞蚊穩問翁窩我尾委衛未位味畏胃喂慰午伍武侮舞勿務物誤悟沃臥握烏汙嗚屋無吳五稀溪錫熄膝習席襲洗喜霧夕西吸希析息犧悉惜嚇夏廈仙先纖掀鮮閑弦戲系細隙蝦瞎峽狹霞下憲陷餡羨獻鄉相香箱詳賢鹹銜嫌顯險縣現線限削宵消銷小曉孝效校笑祥享響想向巷項象像橡瀉卸屑械謝心辛欣新薪些歇協邪脅斜攜鞋寫泄姓幸性凶兄胸雄熊休修信興星腥刑行形型醒杏許序敘緒續絮蓄宣懸旋羞朽秀繡袖鏽須虛需徐訓訊迅壓呀押鴉鴨牙芽選穴學雪血尋巡旬詢循岩沿炎研鹽蜒顏掩眼演崖啞雅亞咽煙淹延嚴言揚羊陽楊洋仰養氧癢樣厭宴豔驗焰雁燕央殃秧耀爺也冶野業葉頁夜液妖腰邀窯謠搖遙咬藥要乙已以蟻倚椅義億憶藝一衣醫依儀宜姨移遺疑毅翼因陰姻音銀引飲隱議亦異役譯易疫益誼意影映硬傭擁庸永詠泳勇印應英櫻鷹迎盈營蠅贏游友有又右幼誘於予餘湧用優憂悠尤由猶郵油雨語玉育鬱獄浴預域欲魚娛漁愉愚榆與宇嶼羽圓援緣源遠怨院願約月禦裕遇愈譽冤元員園原暈韻雜災栽宰載再在咱鑰悅閱躍越雲勻允孕運皂造燥躁則擇澤責賊怎暫贊髒葬遭糟早棗澡灶宅窄債寨沾粘斬展盞嶄增贈渣紮軋閘眨炸榨摘脹障招找召兆趙照罩遮占戰站張章漲掌丈仗帳診枕陣振鎮震爭征掙睜折哲者這浙貞針偵珍真汁芝枝知織肢脂蜘執侄箏蒸整正證鄭政症之支指至志制幟治質秩致智直值職植殖止只旨址紙舟周洲粥宙晝皺驟朱株置中忠終鐘腫種眾重州住助注駐柱祝著築鑄抓珠諸豬蛛竹燭逐主煮囑追准捉桌濁啄著仔姿資爪專磚轉賺莊裝壯狀撞走奏租足族阻組祖鑽嘴滋子紫字自宗棕蹤總縱最罪醉尊遵昨左作坐座做"}; 
                    static ImVector<ImWchar> tchinese_range;
                    ImFontGlyphRangesBuilder tchinese_Glyph;
                    tchinese_Glyph.AddText((const char*)buff);
                    tchinese_Glyph.BuildRanges(&tchinese_range);
                    io.Fonts->AddFontFromMemoryTTF(tchinese.address, tchinese.size, 20.f, std::addressof(font_cfg), tchinese_range.Data);
                    //io.Fonts->AddFontFromMemoryTTF(tchinese.address, tchinese.size,   20.f, std::addressof(font_cfg), io.Fonts->GetGlyphRangesChineseTraditionalCommon());
                }
            }

            // build font atlas
            io.Fonts->GetTexDataAsAlpha8(std::addressof(px), std::addressof(w), std::addressof(h), std::addressof(bpp));
            io.Fonts->Flags |= ImFontAtlasFlags_NoPowerOfTwoHeight;
            io.Fonts->Build();
        }

        GUI::SetDefaultTheme();
        return true;
    }
    
    bool Loop(u64 &key) {
        if (!appletMainLoop())
            return false;
        
        key = ImGui_ImplSwitch_NewFrame();
        ImGui::NewFrame();
        return !(key & HidNpadButton_Plus);
    }
    
    void Render(void) {
        ImGui::Render();
        ImGuiIO &io = ImGui::GetIO(); (void)io;
        glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
        glClearColor(0.00f, 0.00f, 0.00f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplSwitch_RenderDrawData(ImGui::GetDrawData());
        GUI::SwapBuffers();
    }
    
    void Exit(void) {
        ImGui_ImplSwitch_Shutdown();
        GUI::ExitEGL();
    }
}
