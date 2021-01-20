#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
void *espresso_create_context(uint64_t a1, uint64_t a2);
void *espresso_create_plan(void *ctx, uint64_t a2);
int espresso_plan_add_network(void *plan, char *path, uint64_t a3, uint64_t a4[2]);
int espresso_network_compiler_set_metadata_key(uint64_t a1, uint64_t a2, char *key);
int espresso_plan_build(void *plan);
int espresso_dump_ir(void *plan, char **ppath);
int espresso_plan_destroy(void *plan);
int espresso_context_destroy(void *ctx);
};

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage:%s <input directory path of file model.espresso.net under directory *.mlmodelc> <output directory for ANECompiler>\n", argv[0]);
        return -1;
    }
    char ipath[1024], opath[1024];
    ipath[sizeof(ipath) - 1] = '\0';
    opath[sizeof(opath) - 1] = '\0';
    void *ctx = espresso_create_context(10008LL, 0xFFFFFFFFLL);
    void *plan = espresso_create_plan(ctx, 0LL);
    uint64_t vals[2];
    snprintf(ipath, sizeof(ipath) - 1, "%s/model.espresso.net", argv[1]);
    printf("network : %s\n", ipath);
    espresso_plan_add_network(plan, ipath, 0x10020LL, vals);
    //static const char key[] = "{\"isegment\":0,\"inputs\":{\"drawing\":{\"shape\":[28,28,1,1]}},\"outputs\":{\"conv2d_6__activation___output\":{\"shape\":[7,7,64,1]}}}";
    //espresso_network_compiler_set_metadata_key(vals[0], vals[1], key);
    espresso_plan_build(plan);
    strncpy(opath, argv[2], sizeof(opath) - 1);
    printf("out path : %s\n", opath);
    char *opath1 = opath;
    espresso_dump_ir(plan, &opath1);
    espresso_plan_destroy(plan);
    espresso_context_destroy(ctx);
    return 0;
}
