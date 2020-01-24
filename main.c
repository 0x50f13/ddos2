//
//  main.c
//  ddos2
//
//  Created by Andre Zay on 16/01/2020.
//  Copyright © 2020 Andre Zay. All rights reserved.
//

#include <stdio.h>
#include "message.h"
#include "arguments.h"
#include "commons.h"
#include "module.h"
#include "config.h"

int main(int argc, const char * argv[]) {
#pragma mark Logo
    
    printf(ORANGE);
    printf(BOLD);
    printf(BLINK);
    printf(" (    (        )  (\n");
    printf(" )\\ ) )\\ )  ( /(  )\\ )      )\n");
    printf("(()/((()/(  )\\())(()/(   ( /(\n");
    printf("/(_))/(_))((_)\\  /(_))  )(_))\n");
    printf("(_))_(_))_   ((_)(_))   ((_)\n");
    printf(ENDC);
    printf(ORANGE);
    printf(BOLD);
    printf("|   \\|   \\ / _ \\/ __|  |_  )\n");
    printf("| |) | |) | (_) \\__ \\   / /\n");
    printf("|___/|___/ \\___/|___/  /___| \n");
    printf("                       Version %s\n",VERSION);
    printf(ENDC);
#if DEBUG
    set_loglevel(LVL_FULL);
#else
    set_loglevel(LVL_RELEASE);
#endif
    
#pragma mark Intializtion
    
    info("Built with GCC %s at %s %s",__VERSION__,__DATE__,__TIME__);
    ch_local_dir(argv[0]);
    
    arguments_begin();
    modules_begin();
    modules_configure(VERSION);
    modules_load(MODULES_DIR);
    
#pragma mark Arguments
    
    argument_add_compulsory("--module", "Module to run.", ARG_STR);
    argument_add("--ls-modules","List all modules loaded.",ARG_BOOL,argbool(false),true,true);
    argument_add("--mod-summary","Show extended information about module.",ARG_BOOL,argbool(false),true,false);
    argument_add("--ls-ifaces", "List network interfaces.", ARG_BOOL,argbool(false),true,true);//TODO: This is, so called help argument. Should set that after implementing it in arguments.c
    argument_add("--net-no-stats", "Disable packets and byte counting for interfaces", ARG_BOOL, argbool(false),true,false);
    
#pragma mark Parse arguments
    
    arguments_parse(argc, argv, 1);
    
#pragma mark Handle arguments
    
    if(argument_value_get_s("--ls-modules", ARG_BOOL).boolValue){
        modules_list();
        return 0;
    }
    if(argument_value_get_s("--mod-summary", ARG_BOOL).boolValue){
        argvalue value=argument_value_get_s("--module", ARG_STR);
        char* mod_name=value.strValue;
        module_t* module=module_get(mod_name);
        module_summary(module);
    }
    return 0;
}
