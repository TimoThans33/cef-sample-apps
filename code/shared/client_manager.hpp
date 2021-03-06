#ifndef CEF_EXAMPLES_SHARED_CLIENT_MANAGER_H_
#define CEF_EXAMPLES_SHARED_CLIENT_MANAGER_H_


#include <list>

#include "include/base/cef_thread_checker.h"
#include "include/cef_browser.h"

namespace shared {
    class ClientManager {
        public:
            ClientManager();
            ~ClientManager();

            // Returns the singleton instance of this object.
            static ClientManager* GetInstance();

            // Called from CefLifeSpanHandler methods:
            void OnAfterCreated(CefRefPtr<CefBrowser> browser);
            void DoClose(CefRefPtr<CefBrowser> browser);
            void OnBeforeClose(CefRefPtr<CefBrowser> browser);

  // Request that all existing browser windows close.
  void CloseAllBrowsers(bool force_close);
            // Request that all existing browser windows close
            bool IsClosing() const;
        private:
            base::ThreadChecker thread_checker_;

            bool is_closing_;

            // List of existing browsers.
            typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
            BrowserList browser_list_;
    };
} // namespace shared

#endif // SHARED_CLIENT_MANAGER_H