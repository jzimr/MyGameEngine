template<typename Identifier>
TextureHolder<Identifier>::TextureHolder()
	: textureMap()
{
}

template<typename Identifier>
void TextureHolder<Identifier>::load(const Identifier identifier, const std::string fileName)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	assert(texture->loadFromFile(fileName));	//	Load file and check if path is valid

	insertResource(identifier, std::move(texture));
}

template<typename Identifier>
sf::Texture TextureHolder<Identifier>::get(const Identifier identifier) const
{
	//typename std::map<Identifier, std::unique_ptr<sf::Texture>>::iterator foundID;

	auto foundID = textureMap.find(identifier);
	assert(foundID != textureMap.end());		//	Check if parameter identifier exists within map

	return *foundID->second.get();
}

template <typename Identifier>
void TextureHolder<Identifier>::insertResource(Identifier id, std::unique_ptr<sf::Texture> texture)
{
	auto inserted = textureMap.insert(std::make_pair(id, std::move(texture)));
	assert(inserted.second);
}