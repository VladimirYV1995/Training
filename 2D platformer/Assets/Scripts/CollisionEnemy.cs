using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class CollisionEnemy : MonoBehaviour
{
    [SerializeField] private UnityEvent _hit;
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.GetComponent<Enemy>())
        {
            _hit?.Invoke();
        }
    }
    
}
