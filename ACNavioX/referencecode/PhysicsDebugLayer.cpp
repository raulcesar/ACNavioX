void GameScene::debugDrawPhysics(b2World *_world) {
156		-	    const Color4F fillColor(1.0f, 0.0f, 0.0f, 0.3f);
157		-	    const Color4F outlineColor(1.0f, 0.0f, 0.0f, 1.0f);
158		-	
159		-	    _drawNode->clear();
160		-	    for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
161		-	        //Por hora, vamos assumir que so temos circulos....
162		-	        for (b2Fixture *f = b->GetFixtureList(); f; f = f->GetNext()) {
163		-	            b2Shape *s = f->GetShape();
164		-	
165		-	
166		-	            b2CircleShape *circle = (b2CircleShape*) s;
167		-	
168		-	            float radiuspx = circle->m_radius * PTM_RATIO;
169		-	
170		-	            b2Vec2 position = b->GetPosition();
171		-	            auto spritePosition = Point((position.x * PTM_RATIO), (position.y * PTM_RATIO));
172		-	
173		-	
174		-	            static const int CIRCLE_SEG_NUM = 12;
175		-	            Vec2 seg[CIRCLE_SEG_NUM] = {};
176		-	            Vec2 center((position.x * PTM_RATIO), (position.y * PTM_RATIO));
177		-	            CCLOG("Radius: %4.2f Center: %4.2f, %4.2f \n", radiuspx, center.x, center.y);
178		-	
179		-	            for (int i = 0; i < CIRCLE_SEG_NUM; ++i)
180		-	            {
181		-	                float angle = (float)i * M_PI / (float)CIRCLE_SEG_NUM * 2.0f;
182		-	                Vec2 d(radiuspx * cosf(angle), radiuspx * sinf(angle));
183		-	                seg[i] = center + d;
184		-	            }
185		-	
186		-	            _drawNode->drawPolygon(seg, CIRCLE_SEG_NUM, fillColor, 1, outlineColor);
187		-	
188		-	
189		-	        }
190		-	
191		-	
192		-	        //get radius
193		-	        //get center
194		-	        // CCLOG("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
195		-	
196		-	
197		-	
198		-	    }
199		-	
200		-	}