void handlejQuery() {
  server.send_P ( 200, "application/js", jquery_js);
}
void handleRoot() {
  server.send_P ( 200, "text/html", index_html);
}
void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send ( 404, "text/plain", message );
}
void handleCss() {
  server.send_P ( 200, "text/css", style_css);
}
void handleAnalogInStatus() {
  server.send (200, "text/plain", String(readTemperatureSensor()));
}
void handleAnInHtml() {
  server.send_P ( 200, "text/html", anInputs_html);
}


/////////////////////new functions//////////////////////////////
//void handleAfterLogin()
//{
//  server.send_P ( 200, "text/html", after_login_html);
//}
