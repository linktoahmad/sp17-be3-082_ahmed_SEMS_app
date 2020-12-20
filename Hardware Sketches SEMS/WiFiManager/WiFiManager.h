#ifndef WiFiManager_h
#define WiFiManager_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <memory>

extern "C" {
  #include "user_interface.h"
}

const char HTTP_HEADER[] PROGMEM          = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
const char HTTP_STYLE[] PROGMEM           = "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-image:linear-gradient(to right, #4e3fd9, #4287f5);color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;} .l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1em;}</style>";
const char HTTP_SCRIPT[] PROGMEM          = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
const char HTTP_HEADER_END[] PROGMEM      = "</head><body><div style='text-align:left;display:inline-block;min-width:260px;'><img src= 'data:image/png;base64,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'>";
const char HTTP_PORTAL_OPTIONS[] PROGMEM  = "<form action=\"/wifi\" method=\"get\"><button>Configure WiFi</button></form><br/><form action=\"/0wifi\" method=\"get\"><button>Configure WiFi (No Scan)</button></form><br/><form action=\"/i\" method=\"get\"><button>Info</button></form><br/><form action=\"/r\" method=\"post\"><button>Reset</button></form>";
const char HTTP_ITEM[] PROGMEM            = "<div><a href='#p' onclick='c(this)'>{v}</a>&nbsp;<span class='q {i}'>{r}%</span></div>";
const char HTTP_FORM_START[] PROGMEM      = "<form method='get' action='wifisave'><input id='s' name='s' length=32 placeholder='SSID'><br/><input id='p' name='p' length=64 type='password' placeholder='password'><br/>";
const char HTTP_FORM_PARAM[] PROGMEM      = "<br/><input id='{i}' name='{n}' maxlength={l} placeholder='{p}' value='{v}' {c}>";
const char HTTP_FORM_END[] PROGMEM        = "<br/><button type='submit'>save</button></form>";
const char HTTP_SCAN_LINK[] PROGMEM       = "<br/><div class=\"c\"><a href=\"/wifi\">Scan</a></div>";
const char HTTP_SAVED[] PROGMEM           = "<div>Credentials Saved<br />Trying to connect ESP to network.<br />If it fails reconnect to AP to try again</div>";
const char HTTP_END[] PROGMEM             = "</div></body></html>";

#ifndef WIFI_MANAGER_MAX_PARAMS
#define WIFI_MANAGER_MAX_PARAMS 10
#endif

class WiFiManagerParameter {
  public:
    /** 
        Create custom parameters that can be added to the WiFiManager setup web page
        @id is used for HTTP queries and must not contain spaces nor other special characters
    */
    WiFiManagerParameter(const char *custom);
    WiFiManagerParameter(const char *id, const char *placeholder, const char *defaultValue, int length);
    WiFiManagerParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);
    ~WiFiManagerParameter();

    const char *getID();
    const char *getValue();
    const char *getPlaceholder();
    int         getValueLength();
    const char *getCustomHTML();
  private:
    const char *_id;
    const char *_placeholder;
    char       *_value;
    int         _length;
    const char *_customHTML;

    void init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);

    friend class WiFiManager;
};


class WiFiManager
{
  public:
    WiFiManager();
    ~WiFiManager();

    boolean       autoConnect();
    boolean       autoConnect(char const *apName, char const *apPassword = NULL);

    //if you want to always start the config portal, without trying to connect first
    boolean       startConfigPortal();
    boolean       startConfigPortal(char const *apName, char const *apPassword = NULL);

    // get the AP name of the config portal, so it can be used in the callback
    String        getConfigPortalSSID();

    void          resetSettings();

    //sets timeout before webserver loop ends and exits even if there has been no setup.
    //useful for devices that failed to connect at some point and got stuck in a webserver loop
    //in seconds setConfigPortalTimeout is a new name for setTimeout
    void          setConfigPortalTimeout(unsigned long seconds);
    void          setTimeout(unsigned long seconds);

    //sets timeout for which to attempt connecting, useful if you get a lot of failed connects
    void          setConnectTimeout(unsigned long seconds);


    void          setDebugOutput(boolean debug);
    //defaults to not showing anything under 8% signal quality if called
    void          setMinimumSignalQuality(int quality = 8);
    //sets a custom ip /gateway /subnet configuration
    void          setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    //sets config for a static IP
    void          setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    //called when AP mode and config portal is started
    void          setAPCallback( void (*func)(WiFiManager*) );
    //called when settings have been changed and connection was successful
    void          setSaveConfigCallback( void (*func)(void) );
    //adds a custom parameter, returns false on failure
    bool          addParameter(WiFiManagerParameter *p);
    //if this is set, it will exit after config, even if connection is unsuccessful.
    void          setBreakAfterConfig(boolean shouldBreak);
    //if this is set, try WPS setup when starting (this will delay config portal for up to 2 mins)
    //TODO
    //if this is set, customise style
    void          setCustomHeadElement(const char* element);
    //if this is true, remove duplicated Access Points - defaut true
    void          setRemoveDuplicateAPs(boolean removeDuplicates);

  private:
    std::unique_ptr<DNSServer>        dnsServer;
    std::unique_ptr<ESP8266WebServer> server;

    //const int     WM_DONE                 = 0;
    //const int     WM_WAIT                 = 10;

    //const String  HTTP_HEADER = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/><title>{v}</title>";

    void          setupConfigPortal();
    void          startWPS();

    const char*   _apName                 = "no-net";
    const char*   _apPassword             = NULL;
    String        _ssid                   = "";
    String        _pass                   = "";
    unsigned long _configPortalTimeout    = 0;
    unsigned long _connectTimeout         = 0;
    unsigned long _configPortalStart      = 0;

    IPAddress     _ap_static_ip;
    IPAddress     _ap_static_gw;
    IPAddress     _ap_static_sn;
    IPAddress     _sta_static_ip;
    IPAddress     _sta_static_gw;
    IPAddress     _sta_static_sn;

    int           _paramsCount            = 0;
    int           _minimumQuality         = -1;
    boolean       _removeDuplicateAPs     = true;
    boolean       _shouldBreakAfterConfig = false;
    boolean       _tryWPS                 = false;

    const char*   _customHeadElement      = "";

    //String        getEEPROMString(int start, int len);
    //void          setEEPROMString(int start, int len, String string);

    int           status = WL_IDLE_STATUS;
    int           connectWifi(String ssid, String pass);
    uint8_t       waitForConnectResult();

    void          handleRoot();
    void          handleWifi(boolean scan);
    void          handleWifiSave();
    void          handleInfo();
    void          handleReset();
    void          handleNotFound();
    void          handle204();
    boolean       captivePortal();
    boolean       configPortalHasTimeout();

    // DNS server
    const byte    DNS_PORT = 53;

    //helpers
    int           getRSSIasQuality(int RSSI);
    boolean       isIp(String str);
    String        toStringIp(IPAddress ip);

    boolean       connect;
    boolean       _debug = true;

    void (*_apcallback)(WiFiManager*) = NULL;
    void (*_savecallback)(void) = NULL;

    int                    _max_params;
    WiFiManagerParameter** _params;

    template <typename Generic>
    void          DEBUG_WM(Generic text);

    template <class T>
    auto optionalIPFromString(T *obj, const char *s) -> decltype(  obj->fromString(s)  ) {
      return  obj->fromString(s);
    }
    auto optionalIPFromString(...) -> bool {
      DEBUG_WM("NO fromString METHOD ON IPAddress, you need ESP8266 core 2.1.0 or newer for Custom IP configuration to work.");
      return false;
    }
};

#endif
