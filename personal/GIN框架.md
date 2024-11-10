# GIN学习笔记

## gin路由
### 基本路由
路由（Routing）是由一个 URI（或者叫路径）和一个特定的 HTTP 方法（GET、POST 等）
组成的，涉及到应用如何响应客户端对某个网站节点的访问。
> gin 框架中采用的路由库是基于httprouter做的
```
package main

import (
    "net/http"

    "github.com/gin-gonic/gin"
)

func main() {
    r := gin.Default()
    r.GET("/", func(c *gin.Context) {
        c.String(http.StatusOK, "hello word")
    })
    r.POST("/xxxpost",getting)
    r.PUT("/xxxput")
    //监听端口默认为8080
    r.Run(":8000")
}
```
### RESTful风格 API 
> gin支持Restful风格的API

RESTful即Representational State Transfer的缩写。直接翻译的意思是"表现层状态转化"，是一种互联网应用程序的API设计理念：URL定位资源，用HTTP描述操作

```
1.获取文章 /blog/getXxx Get blog/Xxx

2.添加 /blog/addXxx POST blog/Xxx

3.修改 /blog/updateXxx PUT blog/Xxx

4.删除 /blog/delXxxx DELETE blog/Xxx
```

### API参数
> 可以通过Context的Param方法来获取API参数(路径中的参数)

```
func main() {
    r := gin.Default()
    r.GET("user/:name/*path", func(c *gin.Context) {
		name := c.Param("name")
		path := c.Param("path")
		fmt.Println(name, path)
		c.String(http.StatusOK, name+path)
	})
    //默认为监听8080端口
    r.Run(":8000")
}
```

### URL参数
> URL参数可以通过DefaultQuery()或Query()方法获取
> DefaultQuery()若参数不存在，返回默认值，Query()若不存在，返回空串
> 示例 http://139.159.160.149:8000/user?name=pexlor

```
r.GET("/user", func(c *gin.Context) {
    // name := c.Query("name")
    name := c.DefaultQuery("name", "pexlor")
    c.String(http.StatusOK, name)
})
```

### 表单(form)参数
> 表单传输为post请求
> 表单参数可以通过PostForm()方法获取
> 示例：建议使用HTTP接口在线测试模拟POST请求

```
r.POST("/form", func(c *gin.Context) {
    types := c.DefaultPostForm("type", "post")
    username := c.PostForm("username")
    password := c.PostForm("password")
    c.String(http.StatusOK, types+username+password)
})
```

### 上传单个文件
> multipart/form-data格式用于文件上传
```
func main() {
    r := gin.Default()
    //限制上传最大尺寸
    r.MaxMultipartMemory = 8 << 20
    r.POST("/upload", func(c *gin.Context) {
        file, err := c.FormFile("file")
        if err != nil {
            c.String(500, "上传图片出错")
        }
        // c.JSON(200, gin.H{"message": file.Header.Context})
        c.SaveUploadedFile(file, file.Filename)
        c.String(http.StatusOK, file.Filename)
    })
    r.Run()
}
```
### 上传多个文件
```
func main() {
   // 1.创建路由
   // 默认使用了2个中间件Logger(), Recovery()
   r := gin.Default()
   // 限制表单上传大小 8MB，默认为32MB
   r.MaxMultipartMemory = 8 << 20
   r.POST("/upload", func(c *gin.Context) {
      form, err := c.MultipartForm()
      if err != nil {
         c.String(http.StatusBadRequest, fmt.Sprintf("get err %s", err.Error()))
      }
      // 获取所有图片
      files := form.File["files"]
      // 遍历所有图片
      for _, file := range files {
         // 逐个存
         if err := c.SaveUploadedFile(file, file.Filename); err != nil {
            c.String(http.StatusBadRequest, fmt.Sprintf("upload err %s", err.Error()))
            return
         }
      }
      c.String(200, fmt.Sprintf("upload ok %d files", len(files)))
   })
   //默认端口号是8080
   r.Run(":8000")
}
```
### 路由组
> routes group是为了管理一些相同的URL
#### 简单路由组
```
func main() {
    router := gin.Default()
    //简单的路由组: v1
    v1 := router.Group("/v1")
    {
        v1.POST("/login", loginEndpoint)
        v1.POST("/submit", submitEndpoint)
        v1.POST("/read", readEndpoint)
    }
    //简单的路由组: v2
    v2 := router.Group("/v2")
    {
        v2.POST("/login", loginEndpoint)
        v2.POST("/submit", submitEndpoint)
        v2.POST("/read", readEndpoint)
    }
    router.Run(":8080")
}
```
#### 路由文件分组
> MVC架构路由分层

```
// 新建adminRoutes.go
package routes
import (
    "net/http"
    "github.com/gin-gonic/gin"
)
funcAdminRoutesInit(router *gin.Engine) {
    adminRouter := router.Group("/admin")
    {
        adminRouter.GET("/user", func(c *gin.Context) {
            c.String(http.StatusOK, "用户")
        })
        adminRouter.GET("/news", func(c *gin.Context) {
            c.String(http.StatusOK, "news")
        })
    }
}
```
### 路由原理
>httproter会将所有路由规则构造一颗前缀树

## 数据解析和绑定
### 通过结构体获取参数
>可以基于请求的Content-Type识别请求数据类型并利用反射机制自动提取请求中QueryString、form表单、JSON、XML等
参数到结构体中

```
//注意首字母大写
type Userinfo struct {
    Username string `form:"username" json:"user"`
    Password string `form:"password" json:"password"`
}
```


### 
# 源码学习

# 面试题
