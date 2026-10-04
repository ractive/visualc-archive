# FTPSync 1.0

Synchronises an FTP directory with a local folder in either direction using MFC's
`CFtpConnection`. A document holds a list of sync pairs (server, credentials, remote
and local folder, sync mode, conflict rules); a first-sync dialog and conflict dialogs
resolve differences, a progress dialog shows the transfer, and the app can hide in the
tray. Unfinished (2001-2002). On import, the hard-coded test server, user name, password
and local path in `AddDlg.cpp` were blanked and four serialised test documents were
removed. Two files carry a GPL-2.0 header; the project otherwise states no licence and
is released under the repository licence.
