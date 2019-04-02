#ifndef PSE_DBMAINFUNC_H_
#define PSE_DBMAINFUNC_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

//   加载用户实体;
void MainLoadPlayerEntity( void* );
//   创建用户角色;
void MainCreateRole( void* );

PSE_NAMESPACE_END_DECL

#endif // PSE_DBMAINFUNC_H_;