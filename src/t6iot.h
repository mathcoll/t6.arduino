/*
  t6iot.h - 
  Created by Mathieu Lory <mathieu@internetcollaboratif.info>.
  Sample file to connect t6 api
  - t6 iot: https://api.internetcollaboratif.info
  - Api doc: https://api.internetcollaboratif.info/docs/
*/

#ifndef t6iot_h
#define t6iot_h
#include <Arduino.h>
#include <ArduinoJWT.h>
#include <sha256.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <TaskManager.h>

class T6Object {
	public:
		T6Object();
		void setId(String id);
		void setSecret(String secret);
		void setUA(String ua);
		String id;
		String secret;
		String userAgent;
		int httpPort;
	private:
};
class T6Flow {
	public:
		T6Flow();
		void setId(String id);
		String id;
		String mqtt_topic;
		String unit;
		boolean save;
		boolean publish;
	private:
};

class T6iot: public TaskManager {
  public:
    char* _urlJWT;
    char* _urlIndex;
    char* _urlDataPoint;
    char* _urlObjects;
    char* _urlFlows;
    char* _urlSnippets;
    char* _urlDashboards;
    char* _urlRules;
    char* _urlMqtts;
    char* _urlUsers;
    char* _urlDatatypes;
    char* _urlUnits;
    char* _urlStatus;
    char* _urlOta;
    bool DEBUG;
    String html;
    String defaultHtml;
    String _messageArrived;
    String _userAgent;

    T6iot();
    T6iot(char* httpHost, int httpPort);
    T6iot(char* httpHost, int httpPort, char* _userAgent);
    T6iot(char* httpHost, int httpPort, char* _userAgent, int timeout);
    int init(char* host, int port);
    int init(char* host, int port, char* ua);
    int init(char* host, int port, char* userAgent, int timeout);
    int setWebServerCredentials(const char* t6ObjectWww_username, const char* t6ObjectWww_password);
    int setWebServerCredentials(const char* t6ObjectWww_username, const char* t6ObjectWww_password, const char* t6ObjectWww_realm);
    int webServerAllowCommand(String command);
    String pollWebServer();
    int startWebServer();
    int startWebServer(int port);
    int startWebServer(int port, const char* t6ObjectWww_username, const char* t6ObjectWww_password, const char* t6ObjectWww_realm);
    int setHtml();
    int setHtml(String html);
    void lockSleep(int timeout);
    void unlockSleep();
    void handleClient();
    void activateOTA();
    bool sleep(String command);

    void setCredentials(const char* t6Username, const char* t6Password);

    void refreshToken();
    void authenticate();
    void authenticate(const char* t6Username, const char* t6Password);
    void authenticateKS();
    void authenticateKS(const char* t6Key, const char* t6Secret);

    void setObject(char* t6ObjectId);
    void setObject(char* t6ObjectId, char* t6ObjectUA);
    void setObject(char* t6ObjectId, char* t6ObjectSecret, char* t6ObjectUA);
	T6Object initObject();
	T6Object initObject(String id);
	T6Object initObject(String id, String secret);
	T6Object initObject(String id, String secret, String ua);

    void getStatus();

    void createDatapoint(char* flowId, DynamicJsonDocument& payload);
    void createDatapoint(char* flowId, DynamicJsonDocument& payload, bool useSignature);
    void getDatapoints();

    void getOtaLatestVersion(String objectId);
    void otaDeploy(const char* sourceId, String objectId);

    String getShowUIHtml(String url);

	void startRest();
	void handle(WiFiClient& client);
	int ledControl(String command);
	int activateOTA(String command);
	int deployOTA();
	int deployOTA(String objectId);
	int upgrade();

	float getValue();
	void setValue(float sensorValue);
	
    void log(const char* logLine);

  private:
	float _sensorValue;
    char* _httpHost;
    int _httpPort;
    int _timeout;
    bool _lockedSleep;
    const char* _t6Username;
    const char* _t6Password;
    const char* _t6Key;
    const char* _t6Secret;
    char* _t6ObjectSecret;
    char* _t6ObjectId;
    int _t6ObjectHttpPort;
    const char* _t6ObjectWww_username;
    const char* _t6ObjectWww_password;
    const char* _t6ObjectWww_realm;
    String _getSignedPayload(String& payload, String& objectId, String& secret);
    String _urlEncode(String str);
};

#endif
