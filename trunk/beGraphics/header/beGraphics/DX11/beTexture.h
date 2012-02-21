/******************************************************/
/* breeze Engine Graphics Module (c) Tobias Zirr 2011 */
/******************************************************/

#ifndef BE_GRAPHICS_TEXTURE_DX11
#define BE_GRAPHICS_TEXTURE_DX11

#include "beGraphics.h"
#include "../beTexture.h"
#include <beCore/beWrapper.h>
#include <D3D11.h>
#include <lean/smart/com_ptr.h>
#include <lean/tags/noncopyable.h>
#include <lean/smart/resource_ptr.h>

namespace beGraphics
{

namespace DX11
{

/// Creates a texture from the given description.
BE_GRAPHICS_DX11_API lean::com_ptr<ID3D11Texture1D, true> CreateTexture(const D3D11_TEXTURE1D_DESC &desc,
	const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Device *pDevice);
/// Creates a texture from the given description.
BE_GRAPHICS_DX11_API lean::com_ptr<ID3D11Texture2D, true> CreateTexture(const D3D11_TEXTURE2D_DESC &desc,
	const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Device *pDevice);
/// Creates a texture from the given description.
BE_GRAPHICS_DX11_API lean::com_ptr<ID3D11Texture3D, true> CreateTexture(const D3D11_TEXTURE3D_DESC &desc,
	const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Device *pDevice);

/// Creates a shader resource view from the given texture.
BE_GRAPHICS_DX11_API lean::com_ptr<ID3D11ShaderResourceView, true> CreateShaderResourceView(ID3D11Resource *pTexture,
	const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, ID3D11Device *pDevice);

/// Maps this texture to allow for CPU access.
BE_GRAPHICS_DX11_API bool Map(ID3D11DeviceContext *pDeviceContext, ID3D11Resource *pTexture, uint4 subResource,
		D3D11_MAPPED_SUBRESOURCE &data, D3D11_MAP map, uint4 flags = 0);
/// Unmaps this texture to allow for GPU access.
BE_GRAPHICS_DX11_API void Unmap(ID3D11DeviceContext *pDeviceContext, ID3D11Resource *pTexture, uint4 subResource);

/// Loads a texture from the given file.
BE_GRAPHICS_DX11_API lean::com_ptr<ID3D11Resource, true> LoadTexture(const lean::utf8_ntri &fileName, const TextureDesc *pDesc, ID3D11Device *pDevice);
/// Loads a texture from the given memory.
BE_GRAPHICS_DX11_API lean::com_ptr<ID3D11Resource, true> LoadTexture(const char *data, uint4 dataLength, const TextureDesc *pDesc, ID3D11Device *pDevice);

/// Creates a texture from the given texture resource.
BE_GRAPHICS_DX11_API lean::resource_ptr<Texture, true> CreateTexture(ID3D11Resource *pTextureResource, beGraphics::TextureCache *pCache = nullptr);

/// Gets a description of the given texture.
BE_GRAPHICS_DX11_API TextureDesc GetDesc(ID3D11Texture1D *pTexture);
/// Gets a description of the given texture.
BE_GRAPHICS_DX11_API TextureDesc GetDesc(ID3D11Texture2D *pTexture);
/// Gets a description of the given texture.
BE_GRAPHICS_DX11_API TextureDesc GetDesc(ID3D11Texture3D *pTexture);
/// Gets a description of the given texture.
BE_GRAPHICS_DX11_API TextureDesc GetDesc(ID3D11Resource *pTexture);

/// Gets the type of the given texture.
BE_GRAPHICS_DX11_API TextureType::T GetType(ID3D11Resource *pTexture);

/// Texture implementation.
class Texture : public beGraphics::Texture
{
private:
	beGraphics::TextureCache *m_pCache;

protected:
	LEAN_INLINE Texture& operator =(const Texture&) { return *this; }

public:
	/// Constructor.
	Texture(beGraphics::TextureCache *pCache)
		: m_pCache(pCache) { }

	/// Gets the stored texture's resource interface.
	virtual ID3D11Resource* GetResource() const = 0;

	/// Gets the texture cache.
	LEAN_INLINE beGraphics::TextureCache* GetCache() const { return m_pCache; }

	/// Gets the implementation identifier.
	LEAN_INLINE ImplementationID GetImplementationID() const { return DX11Implementation; }
};

template <> struct ToImplementationDX11<beGraphics::Texture> { typedef Texture Type; };

// Prototype
template <TextureType::T Type>
class TypedTexture;

/// Converts the given texture type to the corresponding D3D11 texture interface & description types.
template <TextureType::T Type>
struct ToTextureDX11;

template <>
struct ToTextureDX11<TextureType::Texture1D>
{
	typedef ID3D11Texture1D Interface;
	typedef D3D11_TEXTURE1D_DESC Desc;
	typedef TypedTexture<TextureType::Texture1D> Impl;
};
template <>
struct ToTextureDX11<TextureType::Texture2D>
{
	typedef ID3D11Texture2D Interface;
	typedef D3D11_TEXTURE2D_DESC Desc;
	typedef TypedTexture<TextureType::Texture2D> Impl;
};
template <>
struct ToTextureDX11<TextureType::Texture3D>
{
	typedef ID3D11Texture3D Interface;
	typedef D3D11_TEXTURE3D_DESC Desc;
	typedef TypedTexture<TextureType::Texture3D> Impl;
};

/// Texture wrapper.
template <TextureType::T Type>
class TypedTexture
	: public beCore::IntransitiveWrapper< typename ToTextureDX11<Type>::Interface, TypedTexture<Type> >,
	public Texture
{
public:
	/// Texture type.
	static const TextureType::T Type = Type;
	/// Texture description.
	typedef typename ToTextureDX11<Type>::Desc DescType;
	/// Texture type.
	typedef typename ToTextureDX11<Type>::Interface InterfaceType;

private:
	lean::com_ptr<InterfaceType> m_pTexture;

public:
	/// Constructor.
	BE_GRAPHICS_DX11_API TypedTexture(const DescType &desc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Device *pDevice, beGraphics::TextureCache *pCache = nullptr);
	/// Constructor.
	BE_GRAPHICS_DX11_API TypedTexture(InterfaceType *pBuffer, beGraphics::TextureCache *pCache = nullptr);
	/// Destructor.
	BE_GRAPHICS_DX11_API ~TypedTexture();

	/// Maps this texture to allow for CPU access.
	LEAN_INLINE bool Map(ID3D11DeviceContext *pDeviceContext, uint4 subResource,
		D3D11_MAPPED_SUBRESOURCE &data, D3D11_MAP map, uint4 flags = 0)
	{
		return DX11::Map(pDeviceContext, m_pTexture, subResource, data, map, flags);
	}
	/// Unmaps this texture to allow for GPU access.
	LEAN_INLINE void Unmap(ID3D11DeviceContext *pDeviceContext, uint4 subResource)
	{
		DX11::Unmap(pDeviceContext, m_pTexture, subResource);
	}

	/// Gets the texture description.
	LEAN_INLINE TextureDesc GetDesc() const { return DX11::GetDesc(m_pTexture); }
	/// Gets the texture type.
	LEAN_INLINE TextureType::T GetType() const { return Type; };
	
	/// Gets the stored texture's resource interface.
	LEAN_INLINE ID3D11Resource* GetResource() const { return m_pTexture; };

	/// Gets the D3D texture.
	LEAN_INLINE InterfaceType*const& GetInterface() const { return m_pTexture.get(); }
	/// Gets the D3D texture.
	LEAN_INLINE InterfaceType*const& GetTexture() const { return m_pTexture.get(); }
};

/// 1D Texture implementation.
typedef TypedTexture<TextureType::Texture1D> Texture1D;
/// 2D Texture implementation.
typedef TypedTexture<TextureType::Texture2D> Texture2D;
/// 3D Texture implementation.
typedef TypedTexture<TextureType::Texture3D> Texture3D;

#ifdef BE_GRAPHICS_TEXTURE_DX11_INSTANTIATE
	template class TypedTexture<TextureType::Texture1D>;
	template class TypedTexture<TextureType::Texture2D>;
	template class TypedTexture<TextureType::Texture3D>;
#endif

/// Texture view wrapper.
class TextureView
	: public beCore::IntransitiveWrapper<ID3D11ShaderResourceView, TextureView>,
	public beGraphics::TextureView
{
private:
	lean::com_ptr<ID3D11ShaderResourceView> m_pTexture;

	beGraphics::TextureCache *m_pCache;

public:
	/// Constructor.
	BE_GRAPHICS_DX11_API TextureView(ID3D11Resource *pTexture, const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, ID3D11Device *pDevice, beGraphics::TextureCache *pCache = nullptr);
	/// Constructor.
	BE_GRAPHICS_DX11_API TextureView(ID3D11ShaderResourceView *pView, beGraphics::TextureCache *pCache = nullptr);
	/// Destructor.
	BE_GRAPHICS_DX11_API ~TextureView();

	/// Gets the texture description.
	LEAN_INLINE TextureDesc GetDesc() const { return DX11::GetDesc(GetResource()); }
	/// Gets the texture type.
	LEAN_INLINE TextureType::T GetType() const { return DX11::GetType(GetResource()); };
	
	/// Gets the stored view texture's resource interface.
	LEAN_INLINE ID3D11Resource* GetResource() const
	{
		lean::com_ptr<ID3D11Resource> pResource;
		m_pTexture->GetResource(pResource.rebind());
		// Do not keep reference
		return pResource;
	};

	/// Gets the D3D texture.
	LEAN_INLINE ID3D11ShaderResourceView*const& GetInterface() const { return m_pTexture.get(); }
	/// Gets the D3D texture.
	LEAN_INLINE ID3D11ShaderResourceView*const& GetView() const { return m_pTexture.get(); }

	/// Gets the texture cache.
	LEAN_INLINE beGraphics::TextureCache* GetCache() const { return m_pCache; }

	/// Gets the implementation identifier.
	LEAN_INLINE ImplementationID GetImplementationID() const { return DX11Implementation; }
};

template <> struct ToImplementationDX11<beGraphics::TextureView> { typedef TextureView Type; };

/// Scoped mapped texture.
template <class Texture>
struct MappedTexture : public lean::noncopyable
{
private:
	Texture *m_pTexture;
	ID3D11DeviceContext *m_pContext;
	uint4 m_subResource;
	D3D11_MAPPED_SUBRESOURCE m_data;

public:
	/// Maps the given texture in the given device context.
	LEAN_INLINE MappedTexture(Texture *pTexture, ID3D11DeviceContext *pDeviceContext, uint4 subResource, D3D11_MAP map, uint4 flags = 0)
		: m_pTexture(pTexture),
		m_pContext(pDeviceContext),
		m_subResource(subResource)
	{
		Map(m_pContext, m_pTexture, m_subResource, m_data, map, flags);
	}
	/// Unmaps the managed texture.
	LEAN_INLINE ~MappedTexture()
	{
		Unmap();
	}

	/// Unmaps the managed texture.
	LEAN_INLINE void Unmap()
	{
		if (m_data.pData)
		{
			m_data.pData = nullptr;
			DX11::Unmap(m_pContext, m_pTexture, m_subResource);
		}
	}

	/// Gets the mapped data.
	LEAN_INLINE const D3D11_MAPPED_SUBRESOURCE& Data() const { return m_data; }
};

/// Mapped 1D texture.
typedef MappedTexture<Texture1D> MappedTexture1D;
/// Mapped 2D texture.
typedef MappedTexture<Texture2D> MappedTexture2D;
/// Mapped 3D texture.
typedef MappedTexture<Texture3D> MappedTexture3D;


/// Checks whether the given texture is of the given textue type.
LEAN_INLINE bool Is(const beGraphics::Texture *pTex, TextureType::T type)
{
	return (pTex->GetType() == type);
}
/// Casts the given unspecialized texture to its specialized texture type.
template <TextureType::T Type, class Tex>
LEAN_INLINE typename lean::strip_modifiers<Tex>::template undo< TypedTexture<Type> >::type* ToTexUnchecked(Tex *pTex)
{
	// TODO: Casting to *some* ACTIVE IMPLEMENTATION, note how stupid this whole template shit is
	return static_cast< typename lean::strip_modifiers<Tex>::template undo< TypedTexture<Type> >::type* >(pTex);
}
/// Casts the given unspecialized texture to its specialized texture type.
template <TextureType::T Type, class Tex>
LEAN_INLINE typename lean::strip_modifiers<Tex>::template undo< TypedTexture<Type> >::type* ToTex(Tex *pTex)
{
	LEAN_ASSERT( Is(pTex, Type) );
	return ToTexUnchecked<Type>(pTex);
}
/// Casts the given unspecialized texture to its specialized texture type.
template <TextureType::T Type, class Tex>
LEAN_INLINE typename lean::strip_modifiers<Tex>::template undo< TypedTexture<Type> >::type& ToTex(Tex &tex)
{
	return *ToTex<Type>( lean::addressof(tex) );
}
/// Casts the given unspecialized texture to its specialized texture type, if possible.
template <TextureType::T Type, class Tex>
LEAN_INLINE typename lean::strip_modifiers<Tex>::template undo< TypedTexture<Type> >::type* ToTexChecked(Tex *pTex)
{
	return Is(pTex, Type)
		? ToTexUnchecked<Type>(pTex)
		: nullptr;
}

/// Texture view handle.
typedef beCore::QualifiedHandle<beGraphics::TextureView> QualifiedTextureViewHandle;

} // namespace

} // namespace

BE_CORE_DEFINE_QUALIFIED_HANDLE(beGraphics::TextureView, ID3D11ShaderResourceView, beCore::IntransitiveWrapper);

#endif