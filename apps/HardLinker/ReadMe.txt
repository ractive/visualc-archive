HardLinker, Copyright 2000, Jean-Pierre Bergamin
Added NT 4 support, 2000, Armin Gerritsen (armin.gerritsen@philips.com)
-------------------------------------------------

Disclaimer
----------

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version
    (see license.txt for more information)

General Info
------------

HardLinker is a shell extension DLL which allows you to easily create hardlinks.
HardLinks are a new feature on NTFS 5 partitions, provided with Windows 2000.

HardLinks allow that a file (and ONLY files) can have multiple paths to it. When you create
a hardlink to a file, the original file and the hardlink share the same information like
file attributes, file-content etc, but the data is not stored twice.
If you need a file at several positions on your partition, you don't have to copy them any-
more. You just can create hardlinks. This saves you diskspace and all the hardlinks share
always the same content. If you have i.e. an include file you need in every of you project
you can create hardlinks to the original file. When you update one of these hardlinke, all
other links are affected too.

The file system keeps a hard-link reference counter on each file. Only when you delete the
last hardlink of a file, the file is deleted, too.

If you have questions, don't hesitate to ask me:

hardlinker@ractive.ch

More information and updated can be found at:
http://www.ractive.ch/gpl/hardlinker.html


How to use HardLinker
---------------------

HardLinker is a shell extension DLL. This means that you can easily create hardlinke with
explorer.
You can either drag-and-drop a file with your RIGHT mouse-button to a directory of your 
choice and the hardlink is created.
Or you can right-click on a file and specify the location where the hardlink should be
created.

Some limitations:
 - Hardlinks can only be made on file (NOT directories).
 - You only can create hardlinks within the same partition. They can't point to another one.

Installation
------------

The simplest way is to use the installtion/deinstallation program.

If you want to install it manually, you have to take the following steps:

 1. Copy the HardLinker.dll to a directory. The best place is the windows-systemdirectory
    (probably c:\winnt\system32, but this may differ)

 2. Register the dll
    Go to the start-menu and choose "Execute...". Type in the following line:
    regsvr32.exe c:\winnt\system32\HardLinker.dll
    (the path may differ)
    Note that if you run this command on NT 4, without administration
    rights, you may receive an error-warning. The HardLinker.dll should
    have been installed and registerd properly anyway.

 3. Maybe you have to logoff/logon again so that the changes will take effect.

 4. Now you should be able to use the extension

Deinstallation
--------------

Deinstall it under "Start-Settings-Software" if you installed it with the installation
program.

To deinstall is manually you have to take these steps:

 1. Unregister the dll:
    Go to the start-menu and choose "Execute...". Type in the following line:
    regsvr32.exe /u c:\winnt\system32\HardLinker.dll
    (the path may differ)

 2. Now can delete the file c:\winnt\system32\HardLinker.dll

Registry entires
----------------

If you register HardLinker the following registry-settings will be created:

HKEY_CLASSES_ROOT\*\shellex\ContextMenuHandlers\HardLinker
HKEY_CLASSES_ROOT\*\shellex\DragDropHandlers\HardLinker
HKEY_CLASSES_ROOT\Directory\shellex\DragDropHandlers\HardLinker
HKEY_CLASSES_ROOT\CLSID\{38998C6C-0242-4bba-94EB-214D9F49BB8B}


Jean-Pierre Bergamin
james@ractive.ch

-----------------------
Added NT 4 support, 14-12-2000,
Armin Gerritsen
armin.gerritsen@philips.com
