#include <switch.h>

#include "language.hpp"

// TODO: Japanese
static const char *strings_jp[] {
    "OK",
    "Cancel",

    "ファイルブラウザ",
    "ディレクトリ一覧",
    "ファイル名",
    "大きさ",

    "Options",
    "Select All",
    "Clear All",
    "Properties",
    "Rename",
    "New Folder",
    "New File",
    "Copy",
    "Move",
    "Paste",
    "Delete",
    "Set Archive Bit",
    "Enter name",
    "Enter folder name",
    "Enter file name",
    "Copying:",

    "Name: ",
    "Size: ",
    "Created: ",
    "Modified: ",
    "Accessed: ",
    "Width: ",
    "Height: ",

    "This action cannot be undone.",
    "Do you wish to delete the following:",
    "Do you wish to delete ",

    "Extract archive",
    "This action may take a while.",
    "Do you wish to extract ",
    "Extracting:",

    "Settings",
    "Sort Settings",
    "Language",
    "USB",
    "Unmount USB devices",
    "Image Viewer",
    "Developer Options",
    "多言語サポート（無効にすると起動速度が向上します）",
    "完全な文字セットのサポート (アプレット モードでは実行できません）",
    "About",
    "Check for Updates",
    " Display filename",
    " Enable logs",
    " 多言語サポートを有効にする",
    " 完全な文字セットのサポートを有効にする",
    "version",
    "Author",
    "Banner",

    "Update",
    "Could not connect to network.",
    "An update is available.",
    "Do you wish to download and install NX-Shell version ",
    "Update was successful.",
    "Please exit and rerun the application.",
    "You are on the latest version.",

    "Do you wish to unmount all the connected USB devices?",
    "The USB device can now be safely removed.",

    "The name cannot be empty."
};

static const char *strings_en[] {
    "OK",
    "Cancel",

    "File Browser",
    "Directory List",
    "Filename",
    "Size",

    "Options",
    "Select All",
    "Clear All",
    "Properties",
    "Rename",
    "New Folder",
    "New File",
    "Copy",
    "Move",
    "Paste",
    "Delete",
    "Set Archive Bit",
    "Enter name",
    "Enter folder name",
    "Enter file name",
    "Copying:",

    "Name: ",
    "Size: ",
    "Created: ",
    "Modified: ",
    "Accessed: ",
    "Width: ",
    "Height: ",

    "This action cannot be undone.",
    "Do you wish to delete the following:",
    "Do you wish to delete ",

    "Extract archive",
    "This action may take a while.",
    "Do you wish to extract ",
    "Extracting:",

    "Settings",
    "Sort Settings",
    "Language",
    "USB",
    "Unmount USB devices",
    "Image Viewer",
    "Developer Options",
    "Multilingual support (disable to speed up startup)",
    "Full character set support (cannot run in applet mode)",
    "About",
    "Check for Updates",
    " Display filename",
    " Enable logs",
    " Enable support for multi-language",
    " Enable support for full character set",
    "version",
    "Author",
    "Banner",

    "Update",
    "Could not connect to network.",
    "An update is available.",
    "Do you wish to download and install NX-Shell version ",
    "Update was successful.",
    "Please exit and rerun the application.",
    "You are on the latest version.",

    "Do you wish to unmount all the connected USB devices?",
    "The USB device can now be safely removed.",

    "The name cannot be empty."
};

// TODO: French
static const char *strings_fr[] {
    "OK",
    "Cancel",

    "Navigateur de fichiers",
    "Liste des répertoires",
    "Nom de fichier",
    "Taille",

    "Options",
    "Select All",
    "Clear All",
    "Properties",
    "Rename",
    "New Folder",
    "New File",
    "Copy",
    "Move",
    "Paste",
    "Delete",
    "Set Archive Bit",
    "Enter name",
    "Enter folder name",
    "Enter file name",
    "Copying:",

    "Name: ",
    "Size: ",
    "Created: ",
    "Modified: ",
    "Accessed: ",
    "Width: ",
    "Height: ",

    "This action cannot be undone.",
    "Do you wish to delete the following:",
    "Do you wish to delete ",

    "Extract archive",
    "This action may take a while.",
    "Do you wish to extract ",
    "Extracting:",

    "Settings",
    "Sort Settings",
    "Language",
    "USB",
    "Unmount USB devices",
    "Image Viewer",
    "Developer Options",
    "Prise en charge multilingue (désactiver pour accélérer le démarrage)",
    "Prise en charge complète du jeu de caractères (ne peut pas être exécuté en mode applet)",
    "About",
    "Check for Updates",
    " Display filename",
    " Enable logs",
    " Activer la prise en charge du multi-langue",
    " Activer la prise en charge du jeu de caractères complet",
    "version",
    "Author",
    "Banner",

    "Update",
    "Could not connect to network.",
    "An update is available.",
    "Do you wish to download and install NX-Shell version ",
    "Update was successful.",
    "Please exit and rerun the application.",
    "You are on the latest version.",

    "Do you wish to unmount all the connected USB devices?",
    "The USB device can now be safely removed.",

    "The name cannot be empty."
};

static const char *strings_de[] {
    "OK",
    "Abbrechen",

    "Dateibrowser",
    "Verzeichnisliste",
    "Dateiname",
    "Größe",

    "Optionen",
    "Alle auswählen",
    "Alle entfernen",
    "Eigenschaften",
    "Umbenennen",
    "Neuer Ordner",
    "Neue Datei",
    "Kopieren",
    "Verschieben",
    "Einfügen",
    "Löschen",
    "\"Archive Bit\" setzen",
    "Name eingeben",
    "Ordnername eingeben",
    "Dateiname eingeben",
    "Kopiere:",

    "Name: ",
    "Größe: ",
    "Erstellt: ",
    "Geändert: ",
    "Zugegriffen: ",
    "Breite: ",
    "Höhe: ",

    "Dies kann nicht rückgängig gemacht werden.",
    "Möchten Sie Folgendes löschen:",
    "Möchten Sie Folgendes löschen:",

    "Archiv entpacken",
    "Dies kann eine Weile dauern.",
    "Möchten Sie Folgendes extrahieren:",
    "Extrahiere:",

    "Einstellungen",
    "Sortiereinstellung",
    "Sprache",
    "USB",
    "Unmount USB devices",
    "Bildanzeige",
    "Entwickleroptionen",
    "Mehrsprachige Unterstützung (zur Beschleunigung des Starts deaktivieren)",
    "Volle Zeichensatzunterstützung (kann nicht im Applet-Modus ausgeführt werden)",
    "Über",
    "Nach Updates suchen",
    " Dateiname anzeigen",
    " Log aktivieren",
    " Aktivieren Sie die Unterstützung für mehrere Sprachen",
    " Aktivieren Sie die Unterstützung für den vollständigen Zeichensatz",
    "Version",
    "Autor",
    "Banner",

    "Update",
    "Es konnte keine Verbindung zum Netzwerk herstellt werden.",
    "Ein Update ist verfügbar.",
    "Möchten Sie die folgende NX-Shell-Version herunterladen und installieren:",
    "Update war erfolgreich.",
    "Bitte beenden Sie die Anwendung und starten Sie sie erneut.",
    "Sie sind bereits auf der neusten Version.",

    "Do you wish to unmount all the connected USB devices?",
    "The USB device can now be safely removed.",

    "Der Name darf nicht leer sein."
};

// TODO: Italian
static const char *strings_it[] {
    "OK",
    "Cancel",

    "Browser di file",
    "Elenco delle directory",
    "Nome del file",
    "Dimensione",

    "Options",
    "Select All",
    "Clear All",
    "Properties",
    "Rename",
    "New Folder",
    "New File",
    "Copy",
    "Move",
    "Paste",
    "Delete",
    "Set Archive Bit",
    "Enter name",
    "Enter folder name",
    "Enter file name",
    "Copying:",

    "Name: ",
    "Size: ",
    "Created: ",
    "Modified: ",
    "Accessed: ",
    "Width: ",
    "Height: ",

    "This action cannot be undone.",
    "Do you wish to delete the following:",
    "Do you wish to delete ",

    "Extract archive",
    "This action may take a while.",
    "Do you wish to extract ",
    "Extracting:",

    "Settings",
    "Sort Settings",
    "Language",
    "USB",
    "Unmount USB devices",
    "Image Viewer",
    "Developer Options",
    "Supporto multilingue (disabilita per accelerare l'avvio)",
    "Supporto per set di caratteri completo (non può essere eseguito in modalità applet)",
    "About",
    "Check for Updates",
    " Display filename",
    " Enable logs",
    " Abilita il supporto per il multilingua",
    " Abilita il supporto per il set di caratteri completo",
    "version",
    "Author",
    "Banner",

    "Update",
    "Could not connect to network.",
    "An update is available.",
    "Do you wish to download and install NX-Shell version ",
    "Update was successful.",
    "Please exit and rerun the application.",
    "You are on the latest version.",

    "Do you wish to unmount all the connected USB devices?",
    "The USB device can now be safely removed.",

    "The name cannot be empty."
};

//  Spanish
static const char *strings_es[] {
    "Aceptar",
    "Cancelar",

    "Explorador de archivos",
    "Lista de directorios",
    "Nombre del archivo",
    "Tamaño",

    "Opciones",
    "Seleccionar Todo",
    "Limpiar Todo",
    "Propiedades",
    "Renombrar",
    "Nueva Carpeta",
    "Nuevo Archivo",
    "Copiar",
    "Mover",
    "Pegar",
    "Eliminar",
    "Establecer Bit de Archivo",
    "Ingresar Nombre",
    "Ingresar Nombre de Carpeta",
    "Ingresar Nombre de Archivo",
    "Copiando:",

    "Nombre: ",
    "Tamaño: ",
    "Creado: ",
    "Modificado: ",
    "Accedido: ",
    "Ancho: ",
    "Alto: ",

    "Esta acción no se puede deshacer.",
    "Deseas eliminar lo siguiente:",
    "Deseas eliminar ",

    "Extraer archivo",
    "Esta acción puede tomar un tiempo.",
    "Deseas extraer ",
    "Extrayendo:",

    "Ajustes",
    "Ajustes de organización",
    "Idioma",
    "USB",
    "Unmount USB devices",
    "Visualizador de Imagen",
    "Opciones de Desarrollador",
    "Soporte multilingüe (deshabilitar para acelerar el inicio)",
    "Soporte de juego de caracteres completo (no se puede ejecutar en modo subprograma)",
    "Acerca de",
    "Buscar Actualizaciones",
    " Mostrar nombre de archivo",
    " Habilitar logs",
    " Habilitar el soporte para varios idiomas",
    " Habilitar la compatibilidad con el juego de caracteres completo",
    "versión",
    "Autor",
    "Banner",

    "Actualizar",
    "No se puede conectar a la red.",
    "Una actualización está disponible.",
    "Deseas descargar e instalar la versión de NX-Shell ",
    "Actualización exitosa.",
    "Por favor cerrar y reiniciar la aplicación.",
    "Estás en la última versión.",

    "¿Quieres desmontar todos los dispositivos USB conectados?",
    "El dispositivo USB ahora puede ser removido de forma segura.",

    "El nombre no puede estar vacío."
};

// Simplified Chinese ("Chinese")
static const char *strings_sc[] {
    "确定",
    "取消",

    "文件管理器",
    "目录列表",
    "文件名",
    "大小",

    "选项",
    "选择全部",
    "清除全部",
    "属性",
    "重命名",
    "新建文件夹",
    "新建文件",
    "复制",
    "移动",
    "粘贴",
    "删除",
    "设置存档位",
    "输入名字",
    "输入文件夹名",
    "输入文件名",
    "复制: ",

    "文件名: ",
    "大小: ",
    "创建日期: ",
    "最后修改: ",
    "最后访问: ",
    "宽度: ",
    "高度: ",

    "本操作不可逆.",
    "确定删除下列文件吗:",
    "确定删除吗 ",

    "提取归档",
    "本功能需要花费一点时间.",
    "确定提取吗 ",
    "提取中:",

    "设置",
    "排序方式",
    "语言",
    "USB",
    "卸载USB设备",
    "图片查看器",
    "开发人员选项",
    "多语言支持（禁用加速启动）",
    "全字符集支持（不能在Applet模式下运行）",
    "关于",
    "检查更新",
    " 显示文件名",
    " 打开日志",
    " 启用对多语言的支持",
    " 启用对完整字符集的支持",
    "版本",
    "作者",
    "横幅",

    "更新",
    "连接网络失败.",
    "有新版本的更新可用.",
    "您希望下载并安装NX-Shell版本吗 ",
    "更新成功.",
    "请退出并重新运行应用程序.",
    "你使用的是最新版本.",

    "您想卸载所有连接的 USB 设备吗？",
    "现在可以安全地移除 USB 设备。",

    "名称不能为空."
};

// TODO: Korean
static const char *strings_ko[] {
    "확인",
    "취소",

    "파일 탐색기",
    "디렉토리 목록",
    "파일 이름",
    "크기",

    "옵션",
    "모두 선택",
    "모두 지움",
    "속성",
    "이름 바꾸기",
    "새 폴더",
    "새 파일",
    "복사",
    "이동",
    "붙여넣기",
    "삭제",
    "아카이브 비트 설정",
    "이름 입력",
    "폴더 이름 입력",
    "파일 이름 입력",
    "복사 중:",

    "이름: ",
    "크기: ",
    "제작: ",
    "수정: ",
    "접속: ",
    "너비: ",
    "높이: ",

    "이 작업은 취소할 수 없습니다.",
    "다음을 삭제하겠습니까:",
    "삭제하겠습니까 ",

    "파일 해제",
    "이 작업은 시간이 걸릴 수 있습니다.",
    "해제하겠습니까? ",
    "해제 중:",

    "설정",
    "정렬 설정",
    "언어",
    "USB",
    "USB 장치 마운트 해제",
    "이미지 뷰어",
    "개발자 옵션",
    "다국어 지원（시작 속도를 높이려면 비활성화）",
    "전체 문자 집합 지원（애플릿 모드에서 실행할 수 없음）",
    "정보",
    "업데이트 확인",
    " 파일 이름 표시",
    " 로그 활성화",
    " 다국어 지원 활성화",
    " 전체 문자 집합 지원 활성화",
    "버전",
    "제작자",
    "배너",

    "업데이트",
    "네트워크에 연결할 수 없습니다.",
    "업데이트가 가능합니다.",
    "NX-Shell 버전을 다운로드하여 설치하겠습니까? ",
    "업데이트에 성공했습니다.",
    "응용 프로그램을 종료하고 다시 실행하십시오.",
    "최신 버전을 사용 중입니다.",

    "연결된 모든 USB 장치를 마운트 해제하겠습니까?",
    "이제 USB 장치를 안전하게 제거할 수 있습니다.",

    "이름은 공백이 될 수 없습니다."
};

// TODO: Dutch
static const char *strings_nl[] {
    "OK",
    "Cancel",

    "Bestandsverkenner",
    "Directorylijst",
    "Bestandsnaam",
    "Maat",

    "Options",
    "Select All",
    "Clear All",
    "Properties",
    "Rename",
    "New Folder",
    "New File",
    "Copy",
    "Move",
    "Paste",
    "Delete",
    "Set Archive Bit",
    "Enter name",
    "Enter folder name",
    "Enter file name",
    "Copying:",

    "Name: ",
    "Size: ",
    "Created: ",
    "Modified: ",
    "Accessed: ",
    "Width: ",
    "Height: ",

    "This action cannot be undone.",
    "Do you wish to delete the following:",
    "Do you wish to delete ",

    "Extract archive",
    "This action may take a while.",
    "Do you wish to extract ",
    "Extracting:",

    "Settings",
    "Sort Settings",
    "Language",
    "USB",
    "Unmount USB devices",
    "Image Viewer",
    "Developer Options",
    "Meertalige ondersteuning (uitschakelen om opstarten te versnellen)",
    "Volledige tekenset ondersteuning (kan niet draaien in applet-modus)",
    "About",
    "Check for Updates",
    " Display filename",
    " Enable logs",
    " Ondersteuning voor meerdere talen inschakelen",
    " Ondersteuning voor volledige tekenset inschakelen",
    "version",
    "Author",
    "Banner",

    "Update",
    "Could not connect to network.",
    "An update is available.",
    "Do you wish to download and install NX-Shell version ",
    "Update was successful.",
    "Please exit and rerun the application.",
    "You are on the latest version.",

    "Do you wish to unmount all the connected USB devices?",
    "The USB device can now be safely removed.",

    "The name cannot be empty."
};

// Portuguese
static const char *strings_pt[] {
    "OK",
    "Cancelar",

    "Gerenciador de arquivos",
    "Lista de diretórios",
    "nome do arquivo",
    "Tamanho",

    "Opções",
    "Selecionar Tudo",
    "Limpar Tudo",
    "Propriedades",
    "Renomear",
    "Nova Pasta",
    "Novo Arquivo",
    "Copiar",
    "Mover",
    "Colar",
    "Deletar",
    "Definir Bit de Arquivo",
    "Insira o nome",
    "Insira o nome da pasta",
    "Insira o nome do arquivo",
    "Copiando:",

    "Nome: ",
    "Tamanho: ",
    "Criado: ",
    "Modificado: ",
    "Acessado: ",
    "Largura: ",
    "Altura: ",

    "Essa ação não pode ser desfeita.",
    "Você deseja deletar os seguintes:",
    "Você deseja deletar ",

    "Extrair arquivo",
    "Essa ação pode demorar um pouco.",
    "Você deseja extrair ",
    "Extraindo:",

    "Configurações",
    "Configurações de Organização",
    "Idioma",
    "USB",
    "Desmontar dispositivos USB",
    "Visualizador de Imagens",
    "Opções de Desenvolvedor",
    "Suporte multilíngue (desativar inicialização acelerada)",
    "Suporte completo ao conjunto de caracteres (não pode ser executado no modo Applet)",
    "Sobre",
    "Verificar se há Atualizações",
    " Exibir nome de arquivo",
    " Habilitar logs",
    " Habilitar suporte para vários idiomas",
    " Habilitar suporte para conjuntos de caracteres completos",
    "versão",
    "Autor",
    "Banner",

    "Atualizar",
    "Não foi possível se conectar à internet.",
    "Uma atualização está disponível.",
    "Você deseja baixar e instalar NX-Shell versão ",
    "Atualização feita com sucesso.",
    "Por favor, saia e reinicie a aplicação.",
    "Você está na versão mais recente.",

    "Você deseja desmontar todos os dispositivos USB conectados?",
    "O dispositivo USB pode ser removido com segurança.",

    "O nome não pode estar vazio."
};

// TODO: Russian
static const char *strings_ru[] {
    "OK",
    "Cancel",

    "Файловый браузер",
    "Список каталогов",
    "Имя файла",
    "Размер",

    "Options",
    "Select All",
    "Clear All",
    "Properties",
    "Rename",
    "New Folder",
    "New File",
    "Copy",
    "Move",
    "Paste",
    "Delete",
    "Set Archive Bit",
    "Enter name",
    "Enter folder name",
    "Enter file name",
    "Copying:",

    "Name: ",
    "Size: ",
    "Created: ",
    "Modified: ",
    "Accessed: ",
    "Width: ",
    "Height: ",

    "This action cannot be undone.",
    "Do you wish to delete the following:",
    "Do you wish to delete ",

    "Extract archive",
    "This action may take a while.",
    "Do you wish to extract ",
    "Extracting:",

    "Settings",
    "Sort Settings",
    "Language",
    "USB",
    "Unmount USB devices",
    "Image Viewer",
    "Developer Options",
    "Многоязычная поддержка (отключить для ускорения запуска)",
    "Полная поддержка набора символов (не работает в режиме апплета)",
    "About",
    "Check for Updates",
    " Display filename",
    " Enable logs",
    " Включить поддержку многоязычности",
    " Включить поддержку полного набора символов",
    "version",
    "Author",
    "Banner",

    "Update",
    "Could not connect to network.",
    "An update is available.",
    "Do you wish to download and install NX-Shell version ",
    "Update was successful.",
    "Please exit and rerun the application.",
    "You are on the latest version.",

    "Do you wish to unmount all the connected USB devices?",
    "The USB device can now be safely removed.",

    "The name cannot be empty."
};

// Traditional Chinese ("Taiwanese")
static const char *strings_tw[] {
    "確定",
    "取消",

    "文件瀏覽器",
    "目錄列表",
    "文件名",
    "尺寸",

    "選項",
    "選擇全部",
    "清除全部",
    "屬性",
    "重命名",
    "新建文件夾",
    "新建文件",
    "復製",
    "移動",
    "粘貼",
    "刪除",
    "設置存檔位",
    "輸入名字",
    "輸入文件夾名",
    "輸入文件名",
    "復製：",

    "文件名：",
    "大小：",
    "創建日期：",
    "最後修改：",
    "最後訪問：",
    "寬度：",
    "高度：",

    "本操作不可逆。",
    "確定刪除下列文件嗎？",
    "確定刪除嗎？",

    "提取歸檔",
    "本功能需要花費壹點時間。",
    "確定提取嗎？",
    "提取中：",

    "設置",
    "排序方式",
    "語言",
    "USB",
    "卸載USB設備",
    "圖片查看器",
    "開發人員選項",
    "多語言支持（禁用加速啟動）",
    "全字符集支持（不能在小程序模式下運行）",
    "關於",
    "檢查更新",
    " 顯示文件名",
    " 打開日誌",
    " 啟用對多語言的支持",
    " 啟用對完整字符集的支持",
    "版本",
    "作者",
    "橫幅",

    "更新",
    "連接網絡失敗。",
    "有新版本的更新可用。",
    "您希望下載並安裝NX-Shell版本嗎？",
    "更新成功。",
    "請退出並重新運行應用程序。",
    "妳使用的是最新版本。",

    "您想卸載所有連接的USB設備嗎？",
    "現在可以安全地移除USB設備。",

    "名稱不能為空。"
};

const char **strings[Lang::Max] = {
    strings_jp,
    strings_en,
    strings_fr,
    strings_de,
    strings_it,
    strings_es,
    strings_sc,
    strings_ko,
    strings_nl,
    strings_pt,
    strings_ru,
    strings_tw
};