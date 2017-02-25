#include <WebServer.h>
#include <MiLightClient.h>
#include <Settings.h>
#include <GithubDownloader.h>

#define MILIGHT_GITHUB_USER "sidoh"
#define MILIGHT_GITHUB_REPO "esp8266_milight_hub"
#define MILIGHT_REPO_WEB_PATH "/web/index.html"

#ifndef _MILIGHT_HTTP_SERVER
#define _MILIGHT_HTTP_SERVER 

typedef std::function<void(void)> SettingsSavedHandler;

class MiLightHttpServer {
public:
  MiLightHttpServer(Settings& settings, MiLightClient*& milightClient)
    : server(WebServer(80)),
      milightClient(milightClient),
      settings(settings)
  { 
    this->applySettings(settings);
  }
  
  void begin();
  void handleClient();
  void onSettingsSaved(SettingsSavedHandler handler);
  
protected:
  ESP8266WebServer::THandlerFunction handleServeFile(
    const char* filename, 
    const char* contentType, 
    const char* defaultText = NULL); 
    
  bool serveFile(const char* file, const char* contentType = "text/html");
  ESP8266WebServer::THandlerFunction handleUpdateFile(const char* filename);
  void applySettings(Settings& settings);
  
  void handleUpdateSettings();
  void handleListenGateway();
  void handleUpdateGroup(const UrlTokenBindings* urlBindings);
  void handleUpdateGateway(const UrlTokenBindings* urlBindings);
  
  void handleDownloadUpdate(const UrlTokenBindings* urlBindings);
  
  File updateFile;
  
  WebServer server;
  Settings& settings;
  MiLightClient*& milightClient;
  SettingsSavedHandler settingsSavedHandler;
  
};

#endif