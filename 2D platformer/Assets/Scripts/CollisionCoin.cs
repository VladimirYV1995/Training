using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class CollisionCoin : MonoBehaviour
{
    [SerializeField] private UnityEvent _pickUp;
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.GetComponent<Coin>())
        {
            _pickUp?.Invoke();
            Destroy(collision.collider.gameObject);
        }
    }
    
}
