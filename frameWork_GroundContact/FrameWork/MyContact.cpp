#include "MyContact.h"

MyGroundContact::MyGroundContact()
{
}
MyGroundContact::~MyGroundContact()
{
}
void MyGroundContact::init(cyclone::Particle * p, double size) {
	if (p)
		particles.push_back(p);
	this->size = size;
}

unsigned MyGroundContact::addContact(cyclone::ParticleContact *contact, unsigned limit) const {
	unsigned count = 0;
	for (int i = 0; i < particles.size(); i++) {
		cyclone::Particle * p = particles[i];
		cyclone::real y = p->getPosition().y;

		//���� �浹�� �Ͼ��? (particle�� ũ�⸦ ����)
		//���� �浹�� �Ͼ�ٸ�
		//contact->contctNormal = ?
		//�浹�� ����� �Ǵ� �� ��ƼŬ ����
		//contact->particles[0] = p;
		//contact->particles[1] = NULL; //��? �ٴ��� ������ü�̹Ƿ�
		//�󸶳� ħ�� �߳�?
		//contact->penetration = ?
		//contact->restitution = 1.0
		//���� �浹�� �Ͼ�ٸ� count�� ������Ű�� contact++�� ����
		if (y < size) {
			contact->contactNormal = p->getVelocity().unit() * -1;
			contact->particle[0] = p;
			contact->particle[1] = NULL;
			contact->penetration = 0 - p->getPosition().y + size;
			contact->restitution = 1.0;
			count++;
		}
		if (count >= limit) return count;
	}
	return count;
}