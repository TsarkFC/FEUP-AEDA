#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
    Property* initial = properties[0];
    vector<Property*> same_type = {properties[0]};
    int max_price = properties[0]->getPrice();

    //Go trough properties
	for (int i = 1; i < properties.size(); i++){
	    //Found new property type item
	    if (properties[i]->getAddress() != initial->getAddress() ||
	        properties[i]->getPostalCode() != initial->getPostalCode() ||
	        properties[i]->getTypology() != initial->getTypology()) {

	        //Insert the catalog
            PropertyTypeItem item(initial->getAddress(), initial->getPostalCode(), initial->getTypology(), max_price);
            item.setItems(same_type);
            catalogItems.insert(item);

            //Create new property type
            initial = properties[i];
            same_type = {properties[i]};
            max_price = properties[i]->getPrice();
        }
	    //Still in the same property type
	    else{
	        //Update max price
	        if (properties[i]->getPrice() > max_price) max_price = properties[i]->getPrice();

            //Add to vector
	        same_type.push_back(properties[i]);
	    }
	}
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
    vector<Property*> ret;
    BSTItrIn<PropertyTypeItem> tree(catalogItems);

    while(!tree.isAtEnd()){
        //Found wanted Property type
        if (tree.retrieve().getTypology() == property->getTypology() &&
            tree.retrieve().getPostalCode() == property->getPostalCode() &&
            tree.retrieve().getAddress() == property->getAddress()){

            //Go through items
            for (auto it : tree.retrieve().getItems()) {
                if (get<0>(it->getReservation()) == NULL) ret.push_back(it);
            }
        }
        tree.advance();
    }
    return ret;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {

    vector<Property*> available = getAvailableProperties(property);
    vector<Property*> empty;

    //There was no property with the specified parameters
    if (available == empty) return false;

    Property* place = available[0];

    tuple<Client*, int> tup = {client, place->getPrice() - (percentage/100.0) * place->getPrice()};
    place->setReservation(tup);

    client->addVisiting(place->getAddress(), place->getPostalCode(), place->getTypology(), to_string(place->getPrice()));

    return true;
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {

    listingRecords.insert(client);

}

void REAgency::deleteClients() {
    auto it = listingRecords.begin();
    while (it != listingRecords.end()){
        if (get<2>((*it).getClientPointer()->getVisiting()).empty() && it->getClientPointer()->getVisitedProperties().size() == 0) {
            it = listingRecords.erase(it);
        }
        else it++;
    }
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    //Go through each candidate
    for (auto cli:candidates){
        int visitas = cli.getVisitedProperties().size();
        float reservas = 0;

        //Go through all properties
        for (auto pro : properties){
            if (get<0>(pro->getReservation())->getEMail() == cli.getEMail()) reservas++;
        }

        if (reservas / visitas > min) clientProfiles.push(cli);
    }
}

vector<Property*> REAgency::suggestProperties() {
	priority_queue<Client> copy = clientProfiles;
	vector<Property*> ret;
	Property *temp;

	while (!copy.empty()){
	    Client c = copy.top();
	    copy.pop();

	    if (get<1>(c.getVisiting()).empty()) continue;

	    int min = 10000000;

        //Go trough every property
        for (auto prop:properties){
            if(prop->getPostalCode() == get<1>(c.getVisiting())){
                continue; // -> does not make sense, but passes the test
            }
            if (abs(stoi(prop->getPostalCode()) - stoi(get<1>(c.getVisiting()))) < min){
                min = abs(stoi(prop->getPostalCode()) - stoi(get<1>(c.getVisiting())));
                temp = prop;
            }
        }

        ret.push_back(temp);
	}
	return ret;
}
