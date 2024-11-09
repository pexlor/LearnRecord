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

```
r.POST("/form", func(c *gin.Context) {
    types := c.DefaultPostForm("type", "post")
    username := c.PostForm("username")
    password := c.PostForm("password")
    c.String(http.StatusOK, types+username+password)
})
```

### 
# 源码学习

# 面试题
