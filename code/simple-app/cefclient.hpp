#ifndef CEFCLIENT_H_
#define CEFCLIENT_H_


#include "include/cef_client.h"
#include "include/wrapper/cef_resource_manager.h"

namespace resource_manager {

    class Client : public CefClient,
                public CefDisplayHandler,
                public CefLifeSpanHandler,
                public CefRequestHandler,
                public CefResourceRequestHandler {
    public:
    Client();

    // CefClient methods:
    CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE { return this; }
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this; }
    CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE { return this; }

    // CefDisplayHandler methods:
    void OnTitleChange(CefRefPtr<CefBrowser> browser,
                        const CefString& title) OVERRIDE;

    // CefLifeSpanHandler methods:
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    // CefRequestHandler methods:
    CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefRequest> request,
        bool is_navigation,
        bool is_download,
        const CefString& request_initiator,
        bool& disable_default_handling) OVERRIDE;

    // CefResourceRequestHandler methods:
    cef_return_value_t OnBeforeResourceLoad(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefRequest> request,
        CefRefPtr<CefRequestCallback> callback) OVERRIDE;
    CefRefPtr<CefResourceHandler> GetResourceHandler(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefRequest> request) OVERRIDE;

    private:
    // Manages the registration and delivery of resources.
    CefRefPtr<CefResourceManager> resource_manager_;

    IMPLEMENT_REFCOUNTING(Client);
    DISALLOW_COPY_AND_ASSIGN(Client);
    };

}  // namespace resource_manager
#endif