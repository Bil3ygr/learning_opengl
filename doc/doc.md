# 学习记录

## 读取PNG图片失败问题

在读取图片时，需要判断图片的`nrChannels`，根据`nrChannels`确定**colorType**，并在调用`glTexImage2D`时，
将**colorType**传入，这样才能正确读取资源到贴图

## 设置shader的uniform sampler2D无效

`glActiveTexture`和`uniform sampler2D`的值不是同一个，`GL_TEXTURE0`的实际值为3w+，
而uniform里需要的则是0、1、2等，因此在设置Int时需要给指定的值，而不能用`GL_TEXTURE0`这些枚举值
